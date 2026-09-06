#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"


int intro() {
	int mode;
	printf(GREEN "\n=========== Welcome to the Clinic System ===========\n" RESET);
	printf(BLUE "1. Admin mode\n" RESET);
	printf(BLUE "2. User mode\n" RESET);
	printf(YELLOW "Choose the mode you want: " RESET);
	scanf("%d", &mode);
	printf(CYAN "--------------------------------------------------\n" RESET);
	return mode;
}

int admin_intro() {
	const int pass = 1234;
	int inp_pass;
	int tries = 3;

	while (tries > 0) {
		printf(YELLOW "Please enter the password (%d tries left): " RESET, tries);
		scanf("%d", &inp_pass);

		if (inp_pass == pass) {
			printf(GREEN "\nPassword is correct\n" RESET);
			printf(CYAN "--------------------------------------------------\n" RESET);
			return 1;
		}
		else {
			tries--;
			if (tries > 0)
				printf(RED "Wrong password, please try again.\n" RESET);
		}
	}

	printf(RED "\nYou have exceeded the maximum number of tries.\n" RESET);
	printf(CYAN "--------------------------------------------------\n" RESET);
	return -1;
}

int admin_choice() {
	int choice;
	printf(GREEN "\n=========== Admin Menu ===========\n" RESET);
	printf(BLUE "1. Add new patient record\n" RESET);
	printf(BLUE "2. Edit patient record\n" RESET);
	printf(BLUE "3. Reserve a slot with the doctor\n" RESET);
	printf(BLUE "4. Cancel reservation\n" RESET);
	printf(YELLOW "Enter your choice: " RESET);
	scanf("%d", &choice);
	printf(CYAN "--------------------------------------------------\n" RESET);
	return choice;
}

int user_intro_choice() {
	printf(GREEN "\n=========== User Menu ===========\n" RESET);
	printf(BLUE "1. View patient record\n" RESET);
	printf(BLUE "2. View today reservations\n" RESET);
	printf(YELLOW "Enter your choice: " RESET);
	int choice;
	scanf("%d", &choice);
	printf(CYAN "--------------------------------------------------\n" RESET);
	return choice;
}

void LinkedList_init(LinkedList* PL) {
	PL->HEAD = NULL;
	PL->size = 0;
}

bool LinkedList_isEmpty(LinkedList* PL) {
	return (PL->HEAD == NULL && PL->size == 0);
}


Node* New_Patient() {
	Node* patient = (Node*)malloc(sizeof(Node));
	int age, id;
	char name[50], gender[50];

	printf(YELLOW "\nEnter New Patient Information:\n" RESET);
	printf(CYAN "Name: ");
	scanf(" %[^\n]%*c", &name);

	printf(CYAN "Age: ");
	scanf("%d", &age);

	printf(CYAN "Gender: ");
	scanf(" %[^\n]%*c", &gender);

	printf(CYAN "ID: ");
	scanf("%d", &id);

	patient->Patient_Data.age = age;
	strcpy(patient->Patient_Data.name, name);
	strcpy(patient->Patient_Data.gender, gender);
	patient->Patient_Data.id = id;

	printf(GREEN "\nPatient record created successfully!\n" RESET);
	printf(CYAN "--------------------------------------------------\n" RESET);

	return patient;
}

int search_id(LinkedList* PL, int id) {
	Node* current = PL->HEAD;

	while (current != NULL) {
		if (current->Patient_Data.id == id) {
			return 0;
		}
		current = current->Next;
	}
	return 1;
}

void LinkedList_insertAtEnd(LinkedList* PL, Patient patientData) {
	Node* PN = (Node*)malloc(sizeof(Node));

	strcpy(PN->Patient_Data.name, patientData.name);
	PN->Patient_Data.age = patientData.age;
	strcpy(PN->Patient_Data.gender, patientData.gender);
	PN->Patient_Data.id = patientData.id;
	PN->Next = NULL;

	if (LinkedList_isEmpty(PL)) {
		PL->HEAD = PN;
	}
	else {
		Node* TempNode = PL->HEAD;
		while (TempNode->Next != NULL) {
			TempNode = TempNode->Next;
		}
		TempNode->Next = PN;
	}

	PL->size++;
	printf(GREEN "\nPatient successfully added to the system.\n" RESET);
	printf(CYAN "--------------------------------------------------\n" RESET);
}

void edit_patient(LinkedList* PL) {
	int id;
	printf(YELLOW "Enter the ID of the patient you want to edit: " RESET);
	scanf("%d", &id);

	if (search_id(PL, id) == 1) {
		printf(RED "\nThe ID is not in the system. Please try again...\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return;
	}

	Node* current = PL->HEAD;
	while (current != NULL) {
		if (current->Patient_Data.id == id) {
			int age, new_id;
			char name[50], gender[50];

			printf(YELLOW "\nEnter updated patient information:\n" RESET);
			printf(CYAN "Name: " RESET);
			scanf(" %[^\n]%*c", name);
			printf(CYAN "Age: " RESET);
			scanf("%d", &age);
			printf(CYAN "Gender: " RESET);
			scanf(" %[^\n]%*c", gender);
			printf(CYAN "New ID: " RESET);
			scanf("%d", &new_id);

			current->Patient_Data.age = age;
			strcpy(current->Patient_Data.name, name);
			strcpy(current->Patient_Data.gender, gender);
			current->Patient_Data.id = new_id;

			printf(GREEN "\nPatient data updated successfully!\n" RESET);
			printf(CYAN "--------------------------------------------------\n" RESET);
			break;
		}
		current = current->Next;
	}
}

void print_patient_data(LinkedList* PL) {
	int id;
	printf(YELLOW "Enter the ID of the patient you want to view: " RESET);
	scanf("%d", &id);

	if (search_id(PL, id) == 1) {
		printf(RED "\nThe ID is not in the system. Please try again...\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return;
	}

	Node* current = PL->HEAD;
	while (current != NULL) {
		if (current->Patient_Data.id == id) {
			printf(GREEN "\n=========== Patient Record ===========\n" RESET);
			printf(BLUE "Name   : " RESET "%s\n", current->Patient_Data.name);
			printf(BLUE "Gender : " RESET "%s\n", current->Patient_Data.gender);
			printf(BLUE "Age    : " RESET "%d\n", current->Patient_Data.age);
			printf(BLUE "ID     : " RESET "%d\n", current->Patient_Data.id);
			printf(CYAN "--------------------------------------\n" RESET);
			break;
		}
		current = current->Next;
	}
}

int printAvailableSlots(Slot slots[], int size, int slotIndexes[]) {
	printf(YELLOW "\nAvailable Slots:\n" RESET);
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (slots[i].reserved_id == -1) {
			count++;
			slotIndexes[count - 1] = i;
			printf(GREEN "%d. %s\n" RESET, count, slots[i].time);
		}
	}

	if (count == 0) {
		printf(RED "No slots available today.\n" RESET);
	}

	printf(CYAN "--------------------------------------------------\n" RESET);
	return count;
}

int reserve_a_slot(Slot slots[], int size, LinkedList* PL) {
	int Id;
	printf(YELLOW "Please enter the patient ID: " RESET);
	scanf("%d", &Id);

	if (search_id(PL, Id) == 1) {
		printf(RED "The ID is not in the system. Please try again...\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return 0;
	}

	for (int i = 0; i < size; i++) {
		if (slots[i].reserved_id == Id) {
			printf(RED "This patient already has a reservation.\n" RESET);
			printf(CYAN "--------------------------------------------------\n" RESET);
			return 0;
		}
	}

	int slotIndexes[5];
	int availableCount = printAvailableSlots(slots, size, slotIndexes);

	if (availableCount == 0) {
		return 0;
	}

	int choice;
	printf(YELLOW "Please enter the number of the desired slot: " RESET);
	scanf("%d", &choice);

	if (choice < 1 || choice > availableCount) {
		printf(RED "Invalid slot number.\n" RESET);
		return 0;
	}

	int realIndex = slotIndexes[choice - 1];

	if (slots[realIndex].reserved_id == -1) {
		slots[realIndex].reserved_id = Id;
		printf(GREEN "Slot reserved successfully.\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return 1;
	}
	else {
		printf(RED "This slot is already reserved.\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return 0;
	}
}

int cancel_reservation(Slot slots[], int size, LinkedList* PL) {
	int Id;
	printf(YELLOW "Please enter the patient ID: " RESET);
	scanf("%d", &Id);

	if (search_id(PL, Id) == 1) {
		printf(RED "The ID is not in the system. Please try again...\n" RESET);
		printf(CYAN "--------------------------------------------------\n" RESET);
		return 0;
	}

	for (int i = 0; i < size; i++) {
		if (slots[i].reserved_id == Id) {
			slots[i].reserved_id = -1;
			printf(GREEN "The reservation is cancelled successfully\n" RESET);
			printf(CYAN "--------------------------------------------------\n" RESET);
			return 1;
		}
	}

	printf(RED "No reservation found for this ID\n" RESET);
	printf(CYAN "--------------------------------------------------\n" RESET);
	return 0;
}

void today_reservations(Slot slots[], int size) {
	printf(YELLOW "\nToday's Reservations:\n" RESET);
	bool found = false;

	for (int i = 0; i < size; i++) {
		if (slots[i].reserved_id != -1) {
			printf(GREEN "Slot: %s" RESET ", ID: %d\n", slots[i].time, slots[i].reserved_id);
			found = true;
		}
	}

	if (!found) {
		printf(RED "No reservations today.\n" RESET);
	}

	printf(CYAN "--------------------------------------------------\n" RESET);
}
