-------------------------------------------------------------------------------
--                                                                           --
--  MT32 - Mersenne Twister                                                  --
--  Copyright (C) 2007 HT-LAB 												 --
--                                                                           --
--  Contact : Use feedback form on the website.					             --
--  Web: http://www.ht-lab.com												 --
--  																		 --
--  MT32 files are released under the GNU General Public License.            --
--                                                                           --
-------------------------------------------------------------------------------
--                                                                           --
--  This library is free software; you can redistribute it and/or            --
--  modify it under the terms of the GNU Lesser General Public               --
--  License as published by the Free Software Foundation; either             --
--  version 2.1 of the License, or (at your option) any later version.       --
--                                                                           --
--  This library is distributed in the hope that it will be useful,          --
--  but WITHOUT ANY WARRANTY; without even the implied warranty of           --
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        --
--  Lesser General Public License for more details.                          --
--                                                                           --
--  Full details of the license can be found in the file "copying.txt".      --
--                                                                           --
--  You should have received a copy of the GNU Lesser General Public         --
--  License along with this library; if not, write to the Free Software      --
--  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  --
--                                                                           --
-------------------------------------------------------------------------------
--                                                                           --
--  Counters, instantiated in top level                                      --
-------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;

ENTITY counters IS
   GENERIC( 
      M : integer := 397;
      N : integer := 623
   );
   PORT( 
      clk    : IN     std_logic;
      resetn : IN     std_logic;
      ena    : IN     std_logic;
      wea    : OUT    std_logic;        
      kk_cnt : OUT    std_logic_vector (9 DOWNTO 0);
      km_cnt : OUT    std_logic_vector (9 DOWNTO 0);
      kp_cnt : OUT    std_logic_vector (9 DOWNTO 0);
      wr_cnt : OUT    std_logic_vector (9 DOWNTO 0)
   );

END counters ;

--
ARCHITECTURE rtl OF counters IS

signal kk_cnt_s : std_logic_vector (9 DOWNTO 0);
signal km_cnt_s : std_logic_vector (9 DOWNTO 0);
signal kp_cnt_s : std_logic_vector (9 DOWNTO 0);

signal wr_cnt_s : std_logic_vector (9 DOWNTO 0);

BEGIN
    
process (clk,resetn)  
    begin
        if (resetn='0') then                     
            wea <= '0';                         
        elsif (rising_edge(clk)) then
            wea <= ena;                 -- wea is delayed by 1 clock cycle to       
        end if;                         -- prevent writing outside the dpram address
end process;                            -- address range (0..623)


-------------------------------------------------------------------------------
-- Write counter which is equal to kk-1 
-- Required to achieve single cycle read/write
-------------------------------------------------------------------------------
process (clk,resetn)  
    begin
        if (resetn='0') then                     
            wr_cnt_s <= (others => '1');                            
        elsif (rising_edge(clk)) then
           if (wr_cnt_s = CONV_STD_LOGIC_VECTOR(N,10)) then     
                wr_cnt_s <= (others => '0');            
           elsif ena='1' then       
                wr_cnt_s <= wr_cnt_s + '1'; 
           end if;
        end if;   
end process;
wr_cnt <= wr_cnt_s;


-------------------------------------------------------------------------------
-- kk Counter 
-------------------------------------------------------------------------------
process (clk,resetn)  
    begin
        if (resetn='0') then                     
            kk_cnt_s <= (others => '0');                            
        elsif (rising_edge(clk)) then
           if (kk_cnt_s = CONV_STD_LOGIC_VECTOR(N,10)) then     
                kk_cnt_s <= (others => '0');            
           elsif ena='1' then       
                kk_cnt_s <= kk_cnt_s + '1'; 
           end if;
        end if;   
end process;
kk_cnt <= kk_cnt_s;

-------------------------------------------------------------------------------
-- kp Counter 
-------------------------------------------------------------------------------
process (clk,resetn)  
    begin
        if (resetn='0') then                     
            kp_cnt_s <= "0000000001";                           
        elsif (rising_edge(clk)) then
           if (kp_cnt_s = CONV_STD_LOGIC_VECTOR(N,10)) then     
                kp_cnt_s <= (others => '0');            
           elsif ena='1' then       
                kp_cnt_s <= kp_cnt_s + '1'; 
           end if;
        end if;   
end process;
kp_cnt <= kp_cnt_s;

-------------------------------------------------------------------------------
-- km Counter 
-------------------------------------------------------------------------------
process (clk,resetn)  
    begin
        if (resetn='0') then                     
            km_cnt_s <= CONV_STD_LOGIC_VECTOR(M,10);                            
        elsif (rising_edge(clk)) then
           if (km_cnt_s = CONV_STD_LOGIC_VECTOR(N,10)) then     
                km_cnt_s <= (others => '0');            
           elsif ena='1' then       
                km_cnt_s <= km_cnt_s + '1'; 
           end if;
        end if;   
end process;
km_cnt <= km_cnt_s;
    
end architecture rtl;
