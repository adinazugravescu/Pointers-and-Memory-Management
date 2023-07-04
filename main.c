#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
void printTire (sensor *Sensor, int idx)	//function to print a tire sensor
{
	printf("Tire Sensor\n");
	tire_sensor *data = (tire_sensor *)(Sensor[idx].sensor_data);
	printf("Pressure: %.2f\n", data->pressure);
	printf("Temperature: %.2f\n", data->temperature);
	printf("Wear Level: %d%%\n", data->wear_level);
	if (!(data->performace_score))
		printf("Performance Score: Not Calculated\n");
	else
		printf("Performance Score: %d\n", data->performace_score);
	return;
}
void printPMU (sensor *Sensor, int idx)		//function to print a pmu
{
	printf("Power Management Unit\n");
	power_management_unit *data =
	(power_management_unit *)(Sensor[idx].sensor_data);
	printf("Voltage: %.2f\n", data->voltage);
	printf("Current: %.2f\n", data->current);
	printf("Power Consumption: %.2f\n", data->power_consumption);
	printf("Energy Regen: %d%%\n", data->energy_regen);
	printf("Energy Storage: %d%%\n", data->energy_storage);
	return;
}
int wrongTire (sensor *Sensor, int idx)	//function that returns 1 if the tire is invalid
{
	tire_sensor *data = (tire_sensor *)(Sensor[idx].sensor_data);
	if (data->pressure < 19 || data->pressure > 28 || data->temperature < 0
	|| data->temperature > 120 || data->wear_level < 0 || data->wear_level >
	100)
		return 1;
	return 0;
}
int wrongPmu (sensor *Sensor, int idx)	////function that returns 1 if the PMU is invalid
{
	power_management_unit *data =
	(power_management_unit *)(Sensor[idx].sensor_data);
	if (data->voltage < 10 || data->voltage > 20 || data->current < -100 ||
	 data->current > 100 || data->power_consumption < 0 ||
	 data->power_consumption > 1000 || data->energy_regen < 0 ||
	 data->energy_regen > 100 || data->energy_storage < 0 ||
	 data->energy_storage > 100)
		return 1;
	return 0;
}
void clearSensor (sensor *Sensor, int sizeS, int idx)	//delets the sensor placed at idx index
{
	if (Sensor[idx].sensor_data)
		free(Sensor[idx].sensor_data);
	if (Sensor[idx].operations_idxs)
		free(Sensor[idx].operations_idxs);
	for (int i = idx ; i < sizeS - 1 ; i++)
		Sensor[i] = Sensor[i+1];
	return;
}
void freeSensor (sensor *Sensor, int nr)	//frees the vector of sensors
{
	for (int i = 0 ; i < nr ; i++) {
		free(Sensor[i].sensor_data);
		free(Sensor[i].operations_idxs);
	}
	return;
}
void get_operations(void **operations);
int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("ERROR");
		return -1;
	}
	FILE* fin = fopen(argv[1], "rb");	//binary file that has the number of sensors and the information about each one of them
	int n, type;
	fread(&n, sizeof(int), 1, fin);
	int nInit = n;	//number of sensors
	sensor *Sensor = (sensor *)malloc(n*sizeof(sensor));	//allocation for a sensor vector
	for (int i = 0 ; i < n ; i++) {		//reading the sensors
		fread(&type, sizeof(int), 1, fin);
		if (type == 0) {
			Sensor[i].sensor_type = TIRE;
			tire_sensor *data = (tire_sensor *)malloc(sizeof(tire_sensor));
			fread(&(data->pressure), sizeof(float), 1, fin);
			fread(&(data->temperature), sizeof(float), 1, fin);
			fread(&(data->wear_level), sizeof(int), 1, fin);
			fread(&(data->performace_score), sizeof(int), 1, fin);
			Sensor[i].sensor_data = data;
			int nr_op;
			fread(&(nr_op), sizeof(int), 1, fin);
			Sensor[i].nr_operations = nr_op;
			Sensor[i].operations_idxs = (int *)malloc(nr_op*sizeof(int));
			for (int j = 0 ; j < nr_op ; j++) {
				fread(&(Sensor[i].operations_idxs[j]), sizeof(int), 1, fin);
			}
			continue;
		}
		if (type == 1) {
			Sensor[i].sensor_type = PMU;
			power_management_unit *data =
			(power_management_unit *)malloc(sizeof(power_management_unit));
			fread(&(data->voltage), sizeof(float), 1, fin);
			fread(&(data->current), sizeof(float), 1, fin);
			fread(&(data->power_consumption), sizeof(float), 1, fin);
			fread(&(data->energy_regen), sizeof(int), 1, fin);
			fread(&(data->energy_storage), sizeof(int), 1, fin);
			Sensor[i].sensor_data = data;
			int nr_op;
			fread(&(nr_op), sizeof(int), 1, fin);
			Sensor[i].nr_operations = nr_op;
			Sensor[i].operations_idxs = (int *)malloc(nr_op*sizeof(int));
			for (int j = 0 ; j < nr_op ; j++) {
				fread(&(Sensor[i].operations_idxs[j]), sizeof(int), 1, fin);
			}
		}
	}
	sensor *SensorS = (sensor *)malloc(n*sizeof(sensor)); //vector that stores the sensors acoording to pmu priority
	int k = 0;
	//making a copy of the original vector , placing the pmu's first
	for (int i = 0 ; i < n ; i++) {
		if (Sensor[i].sensor_type == PMU) {
			SensorS[k].sensor_type = PMU;
			SensorS[k].sensor_data = Sensor[i].sensor_data;
			SensorS[k].nr_operations = Sensor[i].nr_operations;
			SensorS[k].operations_idxs  = Sensor[i].operations_idxs;
			k++;
		}
	}
	for (int i = 0 ; i < n ; i++) {
		if (Sensor[i].sensor_type == TIRE) {
			SensorS[k].sensor_type = TIRE;
			SensorS[k].sensor_data = Sensor[i].sensor_data;
			SensorS[k].nr_operations = Sensor[i].nr_operations;
			SensorS[k].operations_idxs  = Sensor[i].operations_idxs;
			k++;
		}
	}

	char **operations = (char **)malloc(8*sizeof(char *));	//allocation of the matrix of operations(functions)
	get_operations((void **)operations);	//call the 
	void (*vectorOp[8])(void *) = {(void *)operations[0], (void *)operations[1],
	(void *)operations[2], (void *)operations[3], (void *)operations[4],
	(void *)operations[5], (void *)operations[6], (void *)operations[7]};
	char com[50];
	while (1) {
		fgets(com, 50, stdin);	//current command
		if (strncmp(com, "print", 5) == 0) {
			int idx = atoi(com+6);
			if (idx < 0 || idx >= n) {
				printf("Index not in range!\n");
				continue;
			}
			if (SensorS[idx].sensor_type == TIRE) {
				printTire(SensorS, idx);
				continue;
			} else {
				printPMU(SensorS, idx);
				continue;
			}
		}
		if (strncmp(com, "analyze", 7) == 0) {
			int idx = atoi(com+8);
			if (idx < 0 || idx >= n) {
				printf("Index not in range!\n");
				continue;
			}
			int nrOp = SensorS[idx].nr_operations;
			for (int a = 0; a < nrOp ; a++) {
				(*vectorOp[SensorS[idx].operations_idxs[a]])
				(SensorS[idx].sensor_data);
			}
		}
		if (strncmp(com, "clear", 5) == 0) {
			int sol = 0;
			for (int c = 0 ; c < n ; c++) {
				if (SensorS[c].sensor_type == TIRE) {
					if (wrongTire(SensorS, c)) {
						sol++;
						clearSensor(SensorS, n, c);
						n--;
						c--;	//index of the next position is actally the current one
					}
				} else
					if (wrongPmu(SensorS, c)) {
						sol++;
						clearSensor(SensorS, n, c);
						n--;
						c--;
					}
				}
			if (sol) {
				SensorS = realloc(SensorS, n*sizeof(sensor));	//in case of wrongTire/PMU , the vector si reallocated
			}
		}
		if (strncmp(com, "exit", 4) == 0) {	//exit means memory deallocation and completion of the program
			freeSensor(Sensor, nInit);
			free(SensorS);
			free(Sensor);
			free(operations);
			fclose(fin);
			return 0;
		}
	}
	return 0;
}
