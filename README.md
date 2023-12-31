# Pointers-and-Memory-Management
*homework


The engineers at Ferrari need your help to win races this season. They have realized that one of the problems with their car is caused by faulty sensors (purchased from AliExpress) that transmit incorrect data to the engineering team. Help the team identify and eliminate the erroneous data to win races.

Implementation

The implementation will involve creating a vector of type Sensor* that will contain two types of sensors: Tire Sensor and Power Management Unit Sensor (see the structures below). A Sensor structure will include the associated sensor data and a vector of indices representing the operations to be performed on the sensor data. There are a total of 8 operations in the form of functions that need to be called on the sensor data. The implementation of these operations can be found in the operations.c file in the skeleton.

To facilitate their use, the following function is provided (also in operations.c) that will build an array of operations:
void get_operations(void** operations)

Priorities

The values received from Power Management Unit sensors are more important than those received from Tire Sensors. Therefore, we want the Power Management Unit sensors to be placed first in the sensor array.

The program will read commands from the keyboard until the "exit" command is received, upon which the program will free the memory and exit.

The received commands will follow the following format:

-print <index> - prints the sensor at the given position, in the required format. If the index received from the keyboard is negative or greater than the 
size of the vector, the message "Index not in range!" will be displayed.

-analyze <index> - performs all operations on the sensor at the given position. If the index received from the keyboard is negative or greater than the size of the vector, the message "Index not in range!" will be displayed.

-clear - removes all sensors that contain erroneous values.

-exit - frees the memory and exits the program.

1. Print (simple)

The printing of the sensor vector will be done following the format below:

For Tire Sensor:

Tire Sensor

Pressure: <pressure>

Temperature: <temperature>

Wear Level: <wear_level>

Performance Score: <computed_score>/Performance Score: Not Calculated

For Power Management Unit Sensor:

Power Management Unit

Voltage: <voltage>

Current: <current>

Power Consumption: <power_consumption>

Energy Regen: <energy_regen>

Energy Storage: <energy_storage>

Printing the float variables will be done with a precision of 2 decimal places.

2. Print (complex)

The sensor vector will be printed in the same format as presented above, taking into account their priorities.

3. Analyze

All operations of the specified sensor will be performed in the order they were given.

4. Clear

Sensors that contain erroneous values will be removed from the vector. A sensor is considered invalid if it does NOT meet at least one of the following conditions:


Tire Sensor:

pressure: between 19 and 28 psi

temperature: between 0°C and 120°C

wear_level: between 0% and 100%


Power Management Unit Sensor:

voltage: between 10V and 20V

current: between -100A and 100A

power_consumption: between 0kW and 1000kW

energy_regen: between 0% and 100%

energy_storage: between 0% and 100%


5. Exit
Upon receiving this command, the memory is deallocated, and the program stops.

File Format for Input

The input files are in binary format.

Example input file:

2 1 12.3 -50 500 30 70 4 4 5 6 7 0 23.5 80 20 0 4 0 1 2 3

Explanation of the file:

2                      // number of sensors

1                      // PMU sensor

12.3 -50 500 30 70     // PMU sensor data

4                      // number of operations to be applied to PMU sensor data

4 5 6 7                // operations to be applied

0                      // Tire sensor

23.5 80 20 0           // Tire sensor data

4                      // number of operations to be applied to Tire sensor data

0 1 2 3                // operations to be applied

The binary file is received as an argument.
