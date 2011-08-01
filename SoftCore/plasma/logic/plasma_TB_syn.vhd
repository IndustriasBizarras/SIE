---------------------------------------------------------------------
-- TITLE: Test Bench
-- AUTHOR: Steve Rhoads (rhoadss@yahoo.com)
-- DATE CREATED: 4/21/01
-- FILENAME: tbench.vhd
-- PROJECT: Plasma CPU core
-- COPYRIGHT: Software placed into the public domain by the author.
--    Software 'as is' without warranty.  Author liable for nothing.
-- DESCRIPTION:
--    This entity provides a test bench for testing the Plasma CPU core.
---------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity plasma_tb is
end; --entity tbench

architecture logic of plasma_tb is
   constant memory_type : string := "TRI_PORT_X";   

   signal clk_in      : std_logic := '1';
   signal rst_in      : std_logic := '0';
   signal addr        : std_logic_vector(12 downto 0);
   signal sram_data   : std_logic_vector(7 downto 0);
   signal nwe         : std_logic;
   signal noe         : std_logic;
   signal ncs         : std_logic;
   signal irq_pin     : std_logic;
   signal led         : std_logic;
   signal TxD         : std_logic;
   signal RxD         : std_logic;

   component plasma
      port(clk_in       : in std_logic;
           rst_in       : in std_logic;
           uart_write   : out std_logic;
           uart_read    : in std_logic;
   
           addr         : in std_logic_vector(12 downto 0);
           sram_data    : in std_logic_vector(7 downto 0);
           nwe          : in std_logic;
           noe          : in std_logic;
           ncs          : in std_logic;
           irq_pin      : out std_logic;
           led          : out std_logic);
   end component; --plasma

begin  --architecture
   clk_in   <= not clk_in after 50 ns;
   rst_in   <= '1' after 500 ns;
   RxD      <= '1';


   u1_plasma: plasma
      PORT MAP (
         clk_in            => clk_in,
         rst_in            => rst_in,
         uart_read         => RxD,
         uart_write        => TxD,
         addr              => addr,
         sram_data         => sram_data,
         nwe               => nwe,
         noe               => noe,
         ncs               => ncs,
         irq_pin           => irq_pin,
         led               => led
     );

end; --architecture logic
