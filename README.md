# Citroen C5 II (2011) instrument panel cluster hacking (STM32G431KB)
Similar story as for the sixth-generation Ford [Mustang (S550)](https://github.com/ufnalski/ford_mustang_cluster_h503rb) and the second-generation Peugeot [308 (T9)](https://github.com/ufnalski/peugeot_308_t9_cluster_g431kb). Let me therefore not to retell the whole story here.

![Citroen C5 IPC in action](/Assets/Images/citroen_c5_ipc_in_action.jpg)

Check [/Assets/Images/](/Assets/Images/) for the pinout.

# Missing files?
Don't worry :slightly_smiling_face: Just hit Alt-K to generate /Drivers/CMCIS/ and /Drivers/STM32G4xx_HAL_Driver/ based on the .ioc file. After a couple of seconds your project will be ready for building.

> [!TIP]
> The IPC uses ISO 11898-3 low-speed (AKA fault-tolerant) CAN at 125 kbit/s. For more details on its physical layer see me embarking on that journey [here](https://github.com/ufnalski/peugeot_308_t9_cluster_g431kb).

# Sources
* [PSA CAN bus](https://autowp.github.io/)
* [PSA VAN-CAN protocol bridge](https://github.com/morcibacsi/PSAVanCanBridge)
* [PSA steering wheel adapter](https://github.com/morcibacsi/PSASteeringWheelAdapter)
* [arduino-psa-comfort-can-adapter](https://github.com/ludwig-v/arduino-psa-comfort-can-adapter)
* [C5 (X7) CAN BUS informations](https://frenchcarforum.co.uk/forum/viewtopic.php?t=80934)
* [Finish sketch for Citroen C5 X7 Nac operation with arduino Can Comfort 2004-2010.](https://www.mittns.de/thread/954-finish-sketch-for-citroen-c5-x7-nac-operation-with-arduino-can-comfort-2004-2010/)
* [How to control Citroen C5 X7 cluster from CANBUS](https://www.youtube.com/watch?v=TrgcHQZ4NFw)
* [Citroen C5 x7 popups on 1E8 CANID](https://www.youtube.com/watch?v=JH-pWpEUefA)
* [Citroen C5 x7 cluster dashboard popups reverse engineering](https://www.youtube.com/watch?v=a4WXy9XJC9c)
* [Citroen C5 licznik polskie komunikaty popup z CANID 1E8](https://www.youtube.com/watch?v=cnaQogS9GoU)
* [RaspberryPI + CAN = Test urządzenia na stole](https://www.youtube.com/watch?v=L7JcIIEqLj0) (Systemy Wbudowane)
* [Can High Speed vs. Can Low Speed – różnice między protokołami](https://systemywbudowane.pl/can-high-speed-vs-can-low-speed-roznice-miedzy-protokolami/) (Systemy Wbudowane)

# Call for action
Create your own [home laboratory/workshop/garage](http://ufnalski.edu.pl/control_engineering_for_hobbyists/2024_dzien_popularyzacji_matematyki/Dzien_Popularyzacji_Matematyki_2024.pdf)! Get inspired by [ControllersTech](https://www.youtube.com/@ControllersTech), [DroneBot Workshop](https://www.youtube.com/@Dronebotworkshop), [Andreas Spiess](https://www.youtube.com/@AndreasSpiess), [GreatScott!](https://www.youtube.com/@greatscottlab), [ElectroBOOM](https://www.youtube.com/@ElectroBOOM), [Phil's Lab](https://www.youtube.com/@PhilsLab), [atomic14](https://www.youtube.com/@atomic14), [That Project](https://www.youtube.com/@ThatProject), [Paul McWhorter](https://www.youtube.com/@paulmcwhorter), [Max Imagination](https://www.youtube.com/@MaxImagination), and many other professional hobbyists sharing their awesome projects and tutorials! Shout-out/kudos to all of them!

> [!WARNING]
> Automotive hacking - do try this at home :sunglasses:

190+ challenges to start from: [Control Engineering for Hobbyists at the Warsaw University of Technology](http://ufnalski.edu.pl/control_engineering_for_hobbyists/Control_Engineering_for_Hobbyists_list_of_challenges.pdf).

Stay tuned!
