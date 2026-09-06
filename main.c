#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

int main() {
    LinkedList patients;
    LinkedList_init(&patients);

    Slot slots[5] = {
        {"2:00pm - 2:30pm", -1},
        {"2:30pm - 3:00pm", -1},
        {"3:00pm - 3:30pm", -1},
        {"4:00pm - 4:30pm", -1},
        {"4:30pm - 5:00pm", -1}
    };

    while (1) {
        int mode = intro();
        if (mode == 1) {
            int pass_res = admin_intro();
            if (pass_res == -1) {
                return 0;
            }
            else {
                int choice = admin_choice();
                if (choice == 1) {
                    printf(CYAN "--------------------------------------------------\n" RESET);
                    Node* add_patient = New_Patient();
                    int id_search = search_id(&patients, add_patient->Patient_Data.id);
                    if (id_search == 0) {
                        printf(RED "The ID is already in the system. Please try again...\n" RESET);
                    }
                    else {
                        LinkedList_insertAtEnd(&patients, add_patient->Patient_Data);
                    }
                }
                else if (choice == 2) {
                    edit_patient(&patients);
                }
                else if (choice == 3) {
                    reserve_a_slot(slots, 5, &patients);
                }
                else if (choice == 4) {
                    cancel_reservation(slots, 5, &patients);
                }
                else {
                    printf(RED "Wrong choice. Please try again...\n" RESET);
                }
            }

        }
        else if (mode == 2) {
            int user_choice = user_intro_choice();
            if (user_choice == 1) {
                print_patient_data(&patients);
            }
            else if (user_choice == 2) {
                today_reservations(slots, 5);
            }
            else {
                printf(RED "Wrong choice. Please try again...\n" RESET);
            }
        }
        else {
            printf(RED "Invalid input. Please try again...\n" RESET);
        }
    }

    return 0;
}
