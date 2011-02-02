-- TITLE: Plasma (CPU core with memory)
-- AUTHOR: Steve Rhoads (rhoadss@yahoo.com)
-- DATE CREATED: 6/4/02
-- FILENAME: plasma.vhd
-- PROJECT: Plasma CPU core
-- COPYRIGHT: Software placed into the public domain by the author.
--    Software 'as is' without warranty.  Author liable for nothing.
-- DESCRIPTION:
--    This entity combines the CPU core with memory and a UART.
--
-- Memory Map:
--   0x00000000 - 0x0000ffff   Internal RAM (8KB)
--   0x10000000 - 0x100fffff   External RAM (1MB)
--   Access all Misc registers with 32-bit accesses
--   0x20000000  Uart Write (will pause CPU if busy)
--   0x20000000  Uart Read
--   0x20000010  IRQ Mask
--   0x20000020  IRQ Status
--   0x20000030  Peripheric 1
--   0x20000040  Peripheric 2
--   0x20000050  Peripheric 3
--   0x20000060  Peripheric 4
--   IRQ bits:
--      1  ^UartWriteBusy
--      0   UartDataAvailable
---------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mlite_pack.all;

entity plasma is
   generic(memory_type : string := "XILINX_16X"; --"DUAL_PORT_" "ALTERA_LPM";
           log_file    : string := "UNUSED");
   port(clk_in         : in std_logic;
        rst_in         : in std_logic;
        uart_write     : out std_logic;
        uart_read      : in std_logic;
        addr           : in std_logic_vector(12 downto 0);
        sram_data      : in std_logic_vector(7 downto 0);
        nwe            : in std_logic;
        noe            : in std_logic;
        ncs            : in std_logic;
        irq_pin        : out std_logic;
        led            : out std_logic
   );
end; --entity plasma

architecture logic of plasma is
   signal reset             : std_logic;
   signal clk               : std_logic;
   signal address_next      : std_logic_vector(31 downto 2);
   signal byte_we_next      : std_logic_vector(3 downto 0);
   signal cpu_address       : std_logic_vector(31 downto 0);
   signal cpu_byte_we       : std_logic_vector(3 downto 0);
   signal cpu_data_w        : std_logic_vector(31 downto 0);
   signal cpu_data_r        : std_logic_vector(31 downto 0);
   signal cpu_pause         : std_logic;

   signal bus_dec           : std_logic_vector(6 downto 0);

   signal data_read_uart    : std_logic_vector(7 downto 0);
   signal data_read_pic     : std_logic_vector(7 downto 0);
   signal write_enable      : std_logic;
   signal mem_busy          : std_logic;

   signal cs_pher           : std_logic;
   signal cs_uart           : std_logic;
   signal cs_pic            : std_logic;
   signal cs_p1             : std_logic;
   signal cs_p2             : std_logic;
   signal cs_p3             : std_logic;
   signal cs_p4             : std_logic;

   signal uart_write_busy   : std_logic;
   signal uart_data_avail   : std_logic;
   signal irq_mask_reg      : std_logic_vector(7 downto 0);
   signal irq_status        : std_logic_vector(7 downto 0);
   signal irq               : std_logic;

   signal cs_ram            : std_logic;
   signal ram_byte_we       : std_logic_vector(3 downto 0);
   signal ram_address       : std_logic_vector(31 downto 2);
   signal ram_data_w        : std_logic_vector(31 downto 0);
   signal ram_data_r        : std_logic_vector(31 downto 0);


begin
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     CLOCK DIVIDER
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   led          <= not(rst_in);
   reset        <= not(rst_in);
   irq_pin      <= not(rst_in);

   clk_div: process(reset, clk, clk_in)
   begin
      if reset = '1' then
         clk <= '0';
      elsif rising_edge(clk_in) then
         clk <= not clk;
      end if;
   end process;

   write_enable <= '1' when cpu_byte_we /= "0000" else '0';
   cpu_pause    <= (uart_write_busy and cs_uart and write_enable);

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     PROCESSOR
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   u1_cpu: mlite_cpu 
      generic map (memory_type => memory_type)
      PORT MAP (
         clk          => clk,
         reset_in     => reset,
         intr_in      => irq,
         address_next => address_next,             --before rising_edge(clk)
         byte_we_next => byte_we_next,
         address      => cpu_address(31 downto 2), --after rising_edge(clk)
         byte_we      => cpu_byte_we,
         data_w       => cpu_data_w,
         data_r       => cpu_data_r,
         mem_pause    => cpu_pause);

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     ADDRESS DECODER
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   cpu_address(1 downto 0)  <= "00";

   addr_decoder: process (cpu_address)
     variable addr_dec : std_logic_vector(6 downto 0);
   begin
     addr_dec   := cpu_address(30 downto 28) & cpu_address(7 downto 4);
     case addr_dec is
       when "0100000" => cs_uart <= '1'; cs_pic <= '0'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '0';
       when "0100001" => cs_uart <= '0'; cs_pic <= '1'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '0';
       when "0100010" => cs_uart <= '0'; cs_pic <= '1'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '0';
       when "0100011" => cs_uart <= '0'; cs_pic <= '0'; cs_p1 <= '1'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '0';
       when "0100100" => cs_uart <= '0'; cs_pic <= '0'; cs_p1 <= '0'; cs_p2 <= '1'; cs_p3 <= '0'; cs_p4 <= '0';
       when "0100101" => cs_uart <= '0'; cs_pic <= '0'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '1'; cs_p4 <= '0';
       when "0100110" => cs_uart <= '0'; cs_pic <= '0'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '1';
       when others    => cs_uart <= '0'; cs_pic <= '0'; cs_p1 <= '0'; cs_p2 <= '0'; cs_p3 <= '0'; cs_p4 <= '0';
     end case;
   end process;

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     BUS MULTIPLEXOR
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  bus_mux: process (cpu_address, ram_data_r, data_read_uart, data_read_pic)
     variable bus_dec : std_logic_vector(4 downto 0);
  begin
     bus_dec   := cpu_address(29) & cpu_address(7 downto 4);
     case bus_dec is
       when "00000" | "00001" | "00010" | "00011" | "00100" | "00101" | "00110" | "00111" |
            "01000" | "01001" | "01010" | "01011" | "01100" | "01101" | "01110" | "01111"  
                    => cpu_data_r <= ram_data_r;
       when "10000" => cpu_data_r <= ZERO(31 downto 8) & data_read_uart;
       when "10001" => cpu_data_r <= ZERO(31 downto 8) & data_read_pic;
       when "10010" => cpu_data_r <= ZERO(31 downto 8) & data_read_pic;
       when "10011" => cpu_data_r <= ZERO;
       when "10100" => cpu_data_r <= ZERO;
       when "10101" => cpu_data_r <= ZERO;
       when "10110" => cpu_data_r <= ZERO;
       when others    => cpu_data_r <= ZERO;
    end case;
--    end if;
  end process;

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                           PIC
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   pic_proc: process(clk, reset, cpu_address, cs_pic, cpu_pause, cpu_byte_we, irq_mask_reg, irq_status, cpu_data_w,
                     uart_write_busy, uart_data_avail)
   begin

     irq_status  <= ZERO(5 downto 0) & not uart_write_busy & uart_data_avail;

     if cs_pic = '1' and cpu_byte_we = "0000" then
       case cpu_address(5 downto 4) is
         when "01"   => data_read_pic <= irq_mask_reg;
         when "10"   => data_read_pic <= irq_status;
         when others => data_read_pic <= ZERO(7 downto 0);
       end case;
     end if;

     if reset = '1' then
       irq_mask_reg  <= ZERO(7 downto 0);
     elsif rising_edge(clk) then
       if cpu_pause = '0' then
         if cs_pic = '1' and cpu_byte_we = "1111" then
           if cpu_address(6 downto 4) = "001" then
             irq_mask_reg <= cpu_data_w(7 downto 0);
           end if;
         end if;
       end if;
     end if;

    if (irq_status and irq_mask_reg) /= ZERO(7 downto 0) then
      irq  <= '1';
    else
      irq  <= '0';
    end if;

   end process;


--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     RAM
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   cs_ram                   <= '1' when address_next(30 downto 28) = "000" else '0';
   ram_address(31 downto 2) <= ZERO(31 downto 13) & address_next(12 downto 2);

   u2_ram: ram 
      generic map (memory_type => memory_type)
      port map (
         clk               => clk,
         enable            => cs_ram,
         write_byte_enable => byte_we_next,
         address           => ram_address,
         data_write        => cpu_data_w,
         data_read         => ram_data_r);

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--                     UART
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   u3_uart: uart
      generic map (log_file => log_file)
      port map(
         clk          => clk,
         reset        => reset,
         cs           => cs_uart,
         nRdWr        => cpu_byte_we(0),
         data_in      => cpu_data_w(7 downto 0),
         data_out     => data_read_uart,
         uart_read    => uart_read,
         uart_write   => uart_write,
         busy_write   => uart_write_busy,
         data_avail   => uart_data_avail);

end; --architecture logic

