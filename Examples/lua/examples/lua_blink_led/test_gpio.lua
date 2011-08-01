package.cpath = "./?.so"
require "gpio"

  PORT_A = 0
  PORT_B = 1
  PORT_C = 2
  PORT_D = 3

  function pulse()
    gpio.set_pin(pio,17)
    delay_s(1)
    gpio.clear_pin(pio,17)
    delay_s(1)
  end

  function delay_s(delay)
    delay = delay or 1
    local time_to = os.time() + delay
    while os.time() < time_to do end
  end

  pio=gpio.open_port(PORT_C)
  gpio.gpio_as_output(pio,17)

  for i=0,5,1 do
    pulse()
  end

