// Colors
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"


typedef struct patient
{
    char name[50];
    int age;
    char gender[50];
    int id;
} Patient;

typedef struct node
{
    Patient Patient_Data;
    struct node* Next;
}Node;

typedef struct linkedList
{
    Node* HEAD;
    int size;
} LinkedList;

typedef struct {
    char time[20];
    int reserved_id;
} Slot;


void LinkedList_init(LinkedList* PL);
bool LinkedList_isEmpty(LinkedList* PL);
void LinkedList_insertAtEnd(LinkedList* PL, Patient patientData);
void print_patient_data(LinkedList* PL);
Node* New_Patient();

int intro();
int admin_intro();
int admin_choice();
int user_intro_choice();
int search_id(LinkedList* PL, int id);
void edit_patient(LinkedList* PL);
int printAvailableSlots(Slot slots[], int size, int slotIndexes[]);
int reserve_a_slot(Slot slots[], int size, LinkedList* PL);
int cancel_reservation(Slot slots[], int size, LinkedList* PL);
void today_reservations(Slot slots[], int size);