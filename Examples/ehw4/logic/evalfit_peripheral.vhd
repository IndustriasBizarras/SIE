-- 07/11/08 
-- Evalfit_peripheral
-- Evalua un arbol de 5 pentarboles, por ahora es valido hasta para *** 14 variables ***
-- Funciona hasta con 14 vars.
-- mapa:
	-- 0	 - 	0x3F	Cromosoma (cada uno con 64-bit)
	-- 0x40 -	0x13F	Objetivo. 16384 bits. Se empieza por el bit 0 MSB.
	

-- Mapa de cromosoma:
	-- bit	bit	Contenido
	--	28	a	31		Nivel del arbol
	--	32	a	47		LUT o tabla del arbol LUT(32)MSB, LUT(47)LSB,
	--	48	a	63		Variables de entrada del arbol (4 bits por variable) 48-51 MSB, 60-63 LSB

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity evalfit_peripheral is
    Port (  clk, reset, habilita: in  STD_LOGIC; 
			maxcombs 			: in  STD_LOGIC_VECTOR (0 to 15);
		  	nivel_max 			: in  STD_LOGIC_VECTOR (0 to 3);
         peripheral_mem_in	: in  STD_LOGIC_VECTOR (0 to 63);
			peripheral_mem_en : out std_logic;
         peripheral_mem_out: out STD_LOGIC_VECTOR (0 to 63);
			peripheral_mem_we : out STD_LOGIC; 
			peripheral_mem_addr: out STD_LOGIC_VECTOR (0 to 8);
			evalfit3_estado	: out std_logic_vector(0 to 15);
			errores				: out  STD_LOGIC_VECTOR (0 to 15);
			fin_ack 			: out std_logic;
			reg0_s				: out  STD_LOGIC_VECTOR (0 to 31);
			reg1_s				: out  STD_LOGIC_VECTOR (0 to 31);			
			reg2_s				: out  STD_LOGIC_VECTOR (0 to 31);			
			reg3_s				: out  STD_LOGIC_VECTOR (0 to 31);
			reg4_s				: out  STD_LOGIC_VECTOR (0 to 31)			
			);
end evalfit_peripheral;

architecture Behavioral of evalfit_peripheral is

function mux16(sel: in std_logic_vector(0 to 3); ent: in std_logic_vector(0 to 15)) return std_logic is
begin
  case sel is
    when "0000" => return ent(15);
    when "0001" => return ent(14);
    when "0010" => return ent(13);
    when "0011" => return ent(12);
    when "0100" => return ent(11);
    when "0101" => return ent(10);
    when "0110" => return ent(9);
    when "0111" => return ent(8);
	 when "1000" => return ent(7);
    when "1001" => return ent(6);
    when "1010" => return ent(5);
    when "1011" => return ent(4);
    when "1100" => return ent(3);
    when "1101" => return ent(2);
    when "1110" => return ent(1);
    when others => return ent(0);
  end case;    
end mux16;

function mux4(sel: in std_logic_vector(0 to 1); ent: in std_logic_vector(0 to 3)) return std_logic is
begin
  case sel is
    when "00" => return ent(3);
    when "01" => return ent(2);
    when "10" => return ent(1);
    when others => return ent(0);
  end case;    
end mux4;

-- senales para evaluar funciones
signal reg0, reg1, reg2, reg3, reg4, regn3, regn4:STD_LOGIC_VECTOR (0 to 31);
signal reg0_sig, reg1_sig, reg2_sig, reg3_sig, reg4_sig, regn3_sig, regn4_sig :STD_LOGIC_VECTOR (0 to 31);
signal sel_aux0, sel_aux1, sel_aux2, sel_aux3, sel_aux4, sel_auxn3, sel_auxn4, sal_arbol, minter_n3, minter_n4 : std_logic_vector(0 to 3);
signal salida_s, fin_ack_sig, fifow_wrreq_sig: std_logic;
signal entrada, errores_aux, errores_sig, salida_nivel : STD_LOGIC_VECTOR (0 to 15);

-- senales para las memorias, guardan resultados de arboles intermedios
signal DO_n2, DI_n2, DO_n3, DI_n3, DO_n4, DI_n4: std_logic_vector(3 downto 0);
signal ADDR_n2, ADDR_n3, ADDR_n4: std_logic_vector(0 to 13);
signal WE_n2, WE_n3, WE_n4: std_logic_vector(3 downto 0);
signal WE_n2_sig, WE_n3_sig, WE_n4_sig: std_logic_vector(3 downto 0);
signal EN_n2, SSR, EN_n3, EN_n4: std_logic;

-- senales para el control
type estado is (reset1, reset2, inicio, proceso, n1, n2, n3, n4, precuenta, cuenta, final, final2);
signal ep, es: estado;
signal nivel, nivel_sig, nivel_reg: std_logic_vector(0 to 3);
signal c1, c1_sig, c2, c2_sig, c3, c3_sig, c4, c4_sig: std_logic_vector(0 to 1);
signal conta, conta_sig, conta2, conta2_sig: std_logic_vector(0 to 15);
signal estado_evalf3, estado_evalf3_sig: std_logic_vector(0 to 15);
signal peripheral_mem_addr_aux, peripheral_mem_addr_sig, peripheral_mem_addr_crom_sig,peripheral_mem_addr_crom : STD_LOGIC_VECTOR (0 to 8);

begin


process(ep, habilita, reg0, reg1, reg2, reg3, reg4, regn3, regn4, nivel, c1, c2, c3, c4, conta, 
		salida_s, salida_nivel, WE_n2, WE_n3, WE_n4, nivel_max,
		maxcombs, peripheral_mem_in, peripheral_mem_addr_crom, peripheral_mem_addr_aux)
begin
es <= reset1;
WE_n2_sig <= "0000";
WE_n3_sig <= "0000";
WE_n4_sig <= "0000";
reg0_sig <= reg0;
reg1_sig <= reg1;
reg2_sig <= reg2;
reg3_sig <= reg3;
reg4_sig <= reg4;
regn3_sig <= regn3;
regn4_sig <= regn4;
conta_sig <= conta;
conta2_sig <= conta2;
c1_sig <= c1;
c2_sig <= c2;
c3_sig <= c3;
c4_sig <= c4;
DI_n2 <= "0000";
DI_n3 <= "0000";
DI_n4 <= "0000";
fin_ack_sig <= '0';
peripheral_mem_addr_sig <= peripheral_mem_addr_aux;
peripheral_mem_addr_crom_sig <= peripheral_mem_addr_crom;
peripheral_mem_we <= '0';
peripheral_mem_en <= '0';
errores_sig <= errores_aux;
nivel_sig <= nivel_reg;
estado_evalf3_sig <= x"FFFF";
case ep is
	when reset1 =>	--poner la memoria a 0000
			WE_n2_sig <= "1111";
			WE_n3_sig <= "1111";
			WE_n4_sig <= "1111";
			conta2_sig <= (others => '0');
			estado_evalf3_sig <= x"0001";
			es <= reset2;
	when reset2 =>
			DI_n2 <= "0000";
			DI_n3 <= "0000";
			DI_n4 <= "0000";
			estado_evalf3_sig <= x"0002";
			if(conta2 = maxcombs)then
				WE_n2_sig <= "0000";
				WE_n3_sig <= "0000";
				WE_n4_sig <= "0000";
				conta2_sig <= (others => '0');
				es <= inicio;
			else
				WE_n2_sig <= "1111";
				WE_n3_sig <= "1111";
				WE_n4_sig <= "1111";
				conta2_sig <= conta2 + 1;
				es <= reset2;
			end if;		
			
	when inicio => 
			if(habilita = '0') then 
				es <= inicio;
				conta_sig <= (others => '0');
				conta2_sig <= (others => '0');
				peripheral_mem_addr_sig <= (others => '0');
				c1_sig <= "00";
				c2_sig <= "00";
				c3_sig <= "00";
				c4_sig <= "00";
				errores_sig <= x"0000";
			else  
				es <= proceso;
				peripheral_mem_en <= '1';
			end if;
			estado_evalf3_sig <= x"0003";

	when proceso => 
			peripheral_mem_en <= '1';
			if(nivel = "0001")then
				case c1 is
					when "00" => reg0_sig <= peripheral_mem_in(32 to 63);
					when "01" => reg1_sig <= peripheral_mem_in(32 to 63);
					when "10" => reg2_sig <= peripheral_mem_in(32 to 63);
					when others => reg3_sig <= peripheral_mem_in(32 to 63);
				end case;
				es <= n1;
			elsif(nivel = "0010")then
				reg4_sig <= peripheral_mem_in(32 to 63);
				WE_n2_sig(conv_integer(c2)) <= '1';
				DI_n2(conv_integer(c2)) <= salida_nivel(2);
				es <= n2;
			elsif(nivel = "0011")then
				regn3_sig <= peripheral_mem_in(32 to 63);
				WE_n3_sig(conv_integer(c3)) <= '1';
				DI_n3(conv_integer(c3)) <= salida_nivel(3);
				es <= n3;
			elsif(nivel = "0100")then
				regn4_sig <= peripheral_mem_in(32 to 63);
				WE_n4_sig(conv_integer(c4)) <= '1';
				DI_n4(conv_integer(c4)) <= salida_nivel(4);
				es <= n4;
			elsif(nivel = "1111")then
				es <= final2;
			end if;
			peripheral_mem_addr_sig <= peripheral_mem_addr_aux + 1;
			peripheral_mem_addr_crom_sig <= peripheral_mem_addr_aux + 1;
			nivel_sig <= nivel;
			estado_evalf3_sig <= peripheral_mem_in(48 to 63);--x"FFE" & nivel;----x"02";

	when n1 =>	
			peripheral_mem_en <= '1';
			c1_sig <= c1 + 1;
			peripheral_mem_addr_sig <= peripheral_mem_addr_aux;
			es <= proceso;
			estado_evalf3_sig <= x"0004";

	when n2 => 	
			WE_n2_sig(conv_integer(c2)) <= '1';
			DI_n2(conv_integer(c2)) <= salida_nivel(2);
			peripheral_mem_en <= '1';
			peripheral_mem_addr_sig <= "001000000" + ('0' & conta(2 to 9));-- esto es para que evalue el pentarbol y guarde en memoria la salida
			es <= precuenta;
			conta2_sig <= (others => '0');
			estado_evalf3_sig <= x"0005";

	when n3 => 	
			WE_n3_sig(conv_integer(c3)) <= '1';
			DI_n3(conv_integer(c3)) <= salida_nivel(3);			
			peripheral_mem_en <= '1';
			peripheral_mem_addr_sig <= "001000000" + ('0' & conta(2 to 9));--
			es <= precuenta;
			conta2_sig <= (others => '0');
			estado_evalf3_sig <= x"0006";

	when n4 => 	
			WE_n4_sig(conv_integer(c4)) <= '1';
			DI_n4(conv_integer(c4)) <= salida_nivel(4);
			peripheral_mem_en <= '1';
			peripheral_mem_addr_sig <= "001000000" + ('0' & conta(2 to 9));--
			es <= precuenta;
			conta2_sig <= (others => '0');
			estado_evalf3_sig <= x"0007";

	when precuenta =>
			WE_n2_sig <= WE_n2;
			WE_n3_sig <= WE_n3;
			WE_n4_sig <= WE_n4;				
			DI_n2(conv_integer(c2)) <= salida_nivel(2);
			DI_n3(conv_integer(c3)) <= salida_nivel(3);
			DI_n4(conv_integer(c4)) <= salida_nivel(4);	
			peripheral_mem_en <= '1';	
			peripheral_mem_addr_sig <= "001000000" + ('0' & conta2(2 to 9));
			conta_sig <= conta;
			conta2_sig <= conta + 1;
			es <= cuenta;
			estado_evalf3_sig <= x"0008";

	when cuenta => 	
			DI_n2(conv_integer(c2)) <= salida_nivel(2);
			DI_n3(conv_integer(c3)) <= salida_nivel(3);
			DI_n4(conv_integer(c4)) <= salida_nivel(4);
			peripheral_mem_en <= '1';
			if(conta = maxcombs)then
				WE_n2_sig <= "0000";
				WE_n3_sig <= "0000";
				WE_n4_sig <= "0000";
				conta_sig <= (others => '0');
				conta2_sig <= (others => '0');
				peripheral_mem_addr_sig <= peripheral_mem_addr_crom;  --direccion de mem donde esta el cromosoma
				es <= final;
			else
				WE_n2_sig <= WE_n2;
				WE_n3_sig <= WE_n3;
				WE_n4_sig <= WE_n4;
				conta_sig <= conta + 1;
				conta2_sig <= conta2 + 1;
				peripheral_mem_addr_sig <= "001000000" + ('0' & conta2(2 to 9));--crear señal conta futura
				if(conta(10 to 15) = "111111")then
					es <= precuenta;
				else
					es <= cuenta;
				end if;
			end if;
			if(nivel_reg = nivel_max)then
				if(salida_nivel(conv_integer(nivel_max)) = peripheral_mem_in(conv_integer(conta(10 to 15))))then
					errores_sig <= errores_aux;
				else
					errores_sig <= errores_aux + 1;
				end if;
			else
				errores_sig <= errores_aux;
			end if;			
			
			estado_evalf3_sig <= x"0009";
				
	when final => 
 			if(nivel_reg = "0010")then
				c2_sig <= c2 + 1;
			elsif(nivel_reg = "0011")then
				c3_sig <= c3 + 1;
			elsif(nivel_reg = "0100")then
				c4_sig <= c4 + 1;
			end if;
			peripheral_mem_en <= '1';
			peripheral_mem_addr_sig <= peripheral_mem_addr_crom;
			es <= proceso;
			estado_evalf3_sig <= x"000A";
			
	when final2 =>
			if(habilita = '1') then 
				es <= final2;
			else  
				es <= inicio;
			end if;	
			fin_ack_sig <= '1';
			estado_evalf3_sig <= x"000B";
	when others => es <= inicio;

	end case;
end process;


process(clk, reset)
begin
	if(reset = '1')then
		ep <= reset1;
		c1 <= "00";
		c2 <= "00";
		c3 <= "00";
		c4 <= "00";
		WE_n2 <= "0000";
		WE_n3 <= "0000";
		WE_n4 <= "0000";
		reg0 <= x"00000000";
		reg1 <= x"00000000";
		reg2 <= x"00000000";
		reg3 <= x"00000000";
		reg4 <= x"00000000";
		regn3 <= x"00000000";
		regn4 <= x"00000000";
		conta <= (others => '0');
		conta2 <= (others => '0');
		fin_ack <= '0';
		peripheral_mem_addr_aux <= "000000000";
	 	peripheral_mem_addr_crom <= "000000000";
		errores_aux <= (others => '0');
		nivel_reg <= "0000";
		estado_evalf3 <= x"0000";
	elsif(rising_edge(clk))then
		ep <= es;
		c1 <= c1_sig;
		c2 <= c2_sig;
		c3 <= c3_sig;
		c4 <= c4_sig;
		WE_n2 <= WE_n2_sig;
		WE_n3 <= WE_n3_sig;
		WE_n4 <= WE_n4_sig;
		reg0 <= reg0_sig;
		reg1 <= reg1_sig;
		reg2 <= reg2_sig;
		reg3 <= reg3_sig;
		reg4 <= reg4_sig;
		regn3 <= regn3_sig;
		regn4 <= regn4_sig;
		conta <= conta_sig;
		conta2 <= conta2_sig;
		fin_ack <= fin_ack_sig;
		peripheral_mem_addr_aux <= peripheral_mem_addr_sig;
		peripheral_mem_addr_crom <= peripheral_mem_addr_crom_sig;
		errores_aux <= errores_sig;
		nivel_reg <= nivel_sig;
		estado_evalf3 <= estado_evalf3_sig;
	end if;
end process;

process(nivel_reg, conta, conta2)
begin
case nivel_reg is
	when "0000" =>
		ADDR_n2 <= conta(2 to 15);
		ADDR_n3 <= conta(2 to 15);
		ADDR_n4 <= conta(2 to 15);
	when "0010" =>
		ADDR_n2 <= conta(2 to 15);
		ADDR_n3 <= conta(2 to 15);
		ADDR_n4 <= conta(2 to 15);
	when "0011" =>
		ADDR_n2 <= conta2(2 to 15);
		ADDR_n3 <= conta(2 to 15);
		ADDR_n4 <= conta(2 to 15);
	when "0100" =>
		ADDR_n2 <= conta(2 to 15);
		ADDR_n3 <= conta2(2 to 15);
		ADDR_n4 <= conta(2 to 15);
	when others =>
		ADDR_n2 <= conta2(2 to 15);
		ADDR_n3 <= conta2(2 to 15);
		ADDR_n4 <= conta2(2 to 15);
end case;

end process;


errores <= errores_aux;
peripheral_mem_addr <= peripheral_mem_addr_aux;
nivel <= peripheral_mem_in(28 to 31);
EN_n2 <= '1';
EN_n3 <= '1';
EN_n4 <= '1';
SSR <= '0';
minter_n3 <= DO_n2;
minter_n4 <= DO_n3;
entrada <= conta;

evalfit3_estado <= estado_evalf3;
reg0_s <= reg0;
reg1_s <= reg1;
reg2_s <= reg2;
reg3_s <= reg3;
reg4_s <= reg4;
salida_nivel(1) <= sal_arbol(3);

sel_aux0(3) <= mux16(reg0(28 to 31), entrada);
sel_aux0(2) <= mux16(reg0(24 to 27), entrada);
sel_aux0(1) <= mux16(reg0(20 to 23), entrada);
sel_aux0(0) <= mux16(reg0(16 to 19), entrada);
sal_arbol(3) <= mux16(sel_aux0, reg0(0 to 15));	-- reg0(0 to 15) = dato_lut

sel_aux1(3) <= mux16(reg1(28 to 31), entrada);
sel_aux1(2) <= mux16(reg1(24 to 27), entrada);
sel_aux1(1) <= mux16(reg1(20 to 23), entrada);
sel_aux1(0) <= mux16(reg1(16 to 19), entrada);
sal_arbol(2) <= mux16(sel_aux1, reg1(0 to 15));

sel_aux2(3) <= mux16(reg2(28 to 31), entrada);
sel_aux2(2) <= mux16(reg2(24 to 27), entrada);
sel_aux2(1) <= mux16(reg2(20 to 23), entrada);
sel_aux2(0) <= mux16(reg2(16 to 19), entrada);
sal_arbol(1) <= mux16(sel_aux2, reg2(0 to 15));

sel_aux3(3) <= mux16(reg3(28 to 31), entrada);
sel_aux3(2) <= mux16(reg3(24 to 27), entrada);
sel_aux3(1) <= mux16(reg3(20 to 23), entrada);
sel_aux3(0) <= mux16(reg3(16 to 19), entrada);
sal_arbol(0) <= mux16(sel_aux3, reg3(0 to 15));

sel_aux4(3) <= mux4(reg4(30 to 31), sal_arbol);		--arbol de 2do nivel
sel_aux4(2) <= mux4(reg4(26 to 27), sal_arbol);
sel_aux4(1) <= mux4(reg4(22 to 23), sal_arbol);
sel_aux4(0) <= mux4(reg4(18 to 19), sal_arbol);
salida_nivel(2) <= mux16(sel_aux4, reg4(0 to 15));

sel_auxn3(3) <= mux4(regn3(30 to 31), minter_n3);	--arboles de 3er nivel
sel_auxn3(2) <= mux4(regn3(26 to 27), minter_n3);
sel_auxn3(1) <= mux4(regn3(22 to 23), minter_n3);
sel_auxn3(0) <= mux4(regn3(18 to 19), minter_n3);
salida_nivel(3) <= mux16(sel_auxn3, regn3(0 to 15));

sel_auxn4(3) <= mux4(regn4(30 to 31), minter_n4);	--arboles de 4to nivel
sel_auxn4(2) <= mux4(regn4(26 to 27), minter_n4);
sel_auxn4(1) <= mux4(regn4(22 to 23), minter_n4);
sel_auxn4(0) <= mux4(regn4(18 to 19), minter_n4);
salida_nivel(4) <= mux16(sel_auxn4, regn4(0 to 15));

ram_nivel20:RAMB16_S1 port map(DO => DO_n2(3 downto 3), ADDR => ADDR_n2, CLK => clk, DI => DI_n2(3 downto 3), EN => EN_n2, SSR => SSR, WE => WE_n2(3));
ram_nivel21:RAMB16_S1 port map(DO => DO_n2(2 downto 2), ADDR => ADDR_n2, CLK => clk, DI => DI_n2(2 downto 2), EN => EN_n2, SSR => SSR, WE => WE_n2(2));
ram_nivel22:RAMB16_S1 port map(DO => DO_n2(1 downto 1), ADDR => ADDR_n2, CLK => clk, DI => DI_n2(1 downto 1), EN => EN_n2, SSR => SSR, WE => WE_n2(1));
ram_nivel23:RAMB16_S1 port map(DO => DO_n2(0 downto 0), ADDR => ADDR_n2, CLK => clk, DI => DI_n2(0 downto 0), EN => EN_n2, SSR => SSR, WE => WE_n2(0));

ram_nivel30:RAMB16_S1 port map(DO => DO_n3(3 downto 3), ADDR => ADDR_n3, CLK => clk, DI => DI_n3(3 downto 3), EN => EN_n3, SSR => SSR, WE => WE_n3(3));
ram_nivel31:RAMB16_S1 port map(DO => DO_n3(2 downto 2), ADDR => ADDR_n3, CLK => clk, DI => DI_n3(2 downto 2), EN => EN_n3, SSR => SSR, WE => WE_n3(2));
ram_nivel32:RAMB16_S1 port map(DO => DO_n3(1 downto 1), ADDR => ADDR_n3, CLK => clk, DI => DI_n3(1 downto 1), EN => EN_n3, SSR => SSR, WE => WE_n3(1));
ram_nivel33:RAMB16_S1 port map(DO => DO_n3(0 downto 0), ADDR => ADDR_n3, CLK => clk, DI => DI_n3(0 downto 0), EN => EN_n3, SSR => SSR, WE => WE_n3(0));

ram_nivel40:RAMB16_S1 port map(DO => DO_n4(3 downto 3), ADDR => ADDR_n4, CLK => clk, DI => DI_n4(3 downto 3), EN => EN_n4, SSR => SSR, WE => WE_n4(3));
ram_nivel41:RAMB16_S1 port map(DO => DO_n4(2 downto 2), ADDR => ADDR_n4, CLK => clk, DI => DI_n4(2 downto 2), EN => EN_n4, SSR => SSR, WE => WE_n4(2));
ram_nivel42:RAMB16_S1 port map(DO => DO_n4(1 downto 1), ADDR => ADDR_n4, CLK => clk, DI => DI_n4(1 downto 1), EN => EN_n4, SSR => SSR, WE => WE_n4(1));
ram_nivel43:RAMB16_S1 port map(DO => DO_n4(0 downto 0), ADDR => ADDR_n4, CLK => clk, DI => DI_n4(0 downto 0), EN => EN_n4, SSR => SSR, WE => WE_n4(0));

end Behavioral;

