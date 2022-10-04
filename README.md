Uno de los riesgos a los que se enfrenta la población en sus domicilios cuando se encuentran en soledad son las caídas y fallecimientos. Según el artículo "Detector automático de caídas y monitorización de actividad para personas mayores" de la Revista española de geriatría y gerontología, el 30 % de las personas mayores se cae al menos una vez al año, lo que representa el 75 % de las víctimas de caídas. Esta revista también indica que las caídas causan además el 70 % de los accidentes mortales en el colectivo de personas mayores de 75 años, y del incremento del miedo, la ansiedad o la depresión, lo que conduce a la reducción de la actividad diaria de ese colectivo. Estos hechos son la razón del desarrollo de varias soluciones de detección automática de caídas o de prevención, para asegurar una respuesta rápida en caso de que tal evento ocurra. Sin embargo, hoy día se utilizan pocos sistemas comerciales, debido a problemas de fiabilidad, facilidad de instalación y uso, o bien porque las personas no aceptan el dispositivo, por diversos motivos, como rechazo tecnológico o simplemente por su coste.

Como resultado de estas reflexiones que suponen una oportunidad, la motivación y objetivo principal de este proyecto es diseñar y desarrollar un sistema de detección de ausencia de movimiento o respiración.

El proyecto tiene un desarrollo asociado para otra finalidad. Se parte de este desarrollo previo, a partir del cual, se desarrollarán los dispositivos adicionales, así como su firmware necesario.

HIZKERA tiene como objetivo el desarrollo de un producto que identifique situaciones de emergencia dentro de un domicilio, como pueden ser caídas incapacitantes para que la víctima pueda avisar a emergencias, o ausencias no programadas, entre las que se pueden encontrar que la persona en cuestión salga de su domicilio y no vuelva de manera involuntaria, un fallecimiento, etc.

La múltiple sensorización (escalable, a su vez) permite detectar movimiento, dirección del movimiento, velocidad, respiración y presencia de CO2. Por tanto, con la combinación adecuada de esas variables, se puede identificar:

Movimiento y velocidad o ausencia de él.
Respiración, sin movimiento (posible caída).
Ni respiración, ni movimiento. El equipo es capaz de diferenciar si la respiración se debe a un animal solo, o al animal + su dueño. Igualmente, el equipo se podría desarrollar para crear patrones de rutina, de manera que, si esa rutina se ve alterada, se pueda actuar, por ejemplo, realizando una llamada de verificación de que está bien, o similar. Esto es, el equipo envía notificación de movimientos y datos de CO2, con esos datos, el sistema receptor (si lo hubiere, ya que no es parte de este proyecto), elabora un patrón de comportamiento o rutina del usuario. Si esa rutina se ve bruscamente modificada, el sistema podría arrojar una alarma. Los métodos de trabajo por tanto son:
El equipo envía alarma por ausencia de movimiento o niveles anormales de CO2.
El equipo envía datos de movimiento y cantidad de CO2, con los que el sistema receptor (no parte de este proyecto), elabora una rutina y actúa ante un cambio repentino de la misma. El equipo se puede conectar sin coste para el usuario, por LORA, redes municipales de IOT, wifi,..
Las actividades necesarias para el desarrollo del equipo son:

Configuración de las prestaciones a desarrollar.
Desarrollo de firmware en función del punto 1.
Prototipado del hardware.
Montaje, calibración y prueba del prototipo (firmware+hardware)
Securizado y validación.
Sept 22. Se comienzan con los trabajos de desarrollo, basados en radar doppler conpatible con sistemas de desarrollo arduino /ESP, etc.