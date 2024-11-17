#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_TEAMS 5
#define SQUAD_SIZE 5
#define NAME_LENGTH 25
#define TEAM_NAME_LENGTH 20

// Struct Definitions
typedef struct {
    char name[NAME_LENGTH];
    int kit_number;
    char position[NAME_LENGTH];
    int day, month, year;  // two structures, one for player: has name, kit number, position and DOB
} player_t;

typedef struct {
    char name[TEAM_NAME_LENGTH];
    player_t players[SQUAD_SIZE];
    int active_size;  // Struct for team, has name, squad size, active players
} team_t;

// Function Prototypes
void display_menu(); //function that displays the menu to choose 
void enroll_club(team_t teams[], int *team_count); //function to add new club
void add_player(team_t teams[], int team_count); //function to add new player
void search_update(team_t teams[], int team_count); //function to search player and update stats
void display_club_statistics(team_t teams[], int team_count); //displays avg age and number of players
void handle_error(const char *message); //function to deal with invalid inputs

int main() {
    team_t teams[NUM_TEAMS];  
    int team_count = 0;

    while (1) { // Infinite loop for menu, switch case used here
        display_menu();
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear newline after scanf

        switch (choice) {
            case 1:
                enroll_club(teams, &team_count);
                break;
            case 2:
                add_player(teams, team_count);
                break;
            case 3:
                search_update(teams, team_count);
                break;
            case 4:
                display_club_statistics(teams, team_count);
                break;
            default:
                printf("Exiting the program.\n");
                return 0;
        }
    }
}

// Displays the main menu
void display_menu() {
    printf("\nMenu:\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search/Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("Any other key to exit\n");
}

// Enroll a new club
void enroll_club(team_t teams[], int *team_count) {
    if (*team_count >= NUM_TEAMS) {
        handle_error("Maximum number of clubs reached."); //if there are more teams than permitted it prints error msg
        return;
    }

    printf("Enter club name: ");
    fgets(teams[*team_count].name, TEAM_NAME_LENGTH, stdin); //gets nae with space
    teams[*team_count].name[strcspn(teams[*team_count].name, "\n")] = '\0'; // remove newline
    teams[*team_count].active_size = 0;
    (*team_count)++; //increases team count
    printf("Club enrolled successfully.\n");
}

// Add a player to a team
void add_player(team_t teams[], int team_count) {
    if (team_count == 0) {
        handle_error("No clubs are enrolled yet.");
        return; //if there are no teams you cant add player
    }

    printf("Select a club:\n");
    for (int i = 0; i < team_count; i++) {
        printf("%d. %s\n", i + 1, teams[i].name); //prints all available clubs
    }

    int club_choice;
    printf("Enter your choice: ");
    scanf("%d", &club_choice); //takes input of chosen club
    while (getchar() != '\n'); // Clear newline after scanf

    if (club_choice < 1 || club_choice > team_count) {
        handle_error("Invalid club selection."); //if the club selection is invalid prints error
        return;
    }

    team_t *selected_team = &teams[club_choice - 1];
    if (selected_team->active_size >= SQUAD_SIZE) {
        handle_error("Team is full."); //if there are more players says that the team is full
        return;
    }

    player_t new_player;
    printf("Enter player name: ");
    fgets(new_player.name, NAME_LENGTH, stdin);
    new_player.name[strcspn(new_player.name, "\n")] = '\0'; // Remove newline

    printf("Enter kit number: "); //entering name and kit number of player
    scanf("%d", &new_player.kit_number);
    while (getchar() != '\n'); // Clear newline after scanf

    printf("Enter position (e.g., Guard, Forward): "); //enter position
    fgets(new_player.position, NAME_LENGTH, stdin);
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; // Remove newline

    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &new_player.day, &new_player.month, &new_player.year); //entering DOB as 3 seperate inputs
    while (getchar() != '\n'); // Clear newline after scanf

    // Check for duplicates
    for (int i = 0; i < selected_team->active_size; i++) {
        if (strcmp(selected_team->players[i].name, new_player.name) == 0 || 
            selected_team->players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate player name or kit number."); //If name or kit number are same it shows error
            return;
        }
    }

    selected_team->players[selected_team->active_size++] = new_player;
    printf("Player added successfully.\n"); //if everything goes through player is enrolled
}

// Search and update player details
void search_update(team_t teams[], int team_count) {
    if (team_count == 0) {
        handle_error("No clubs are enrolled yet.");
        return; 
    }

    char search_name[NAME_LENGTH];
    printf("Enter player name to search: "); //entering player name to search
    fgets(search_name, NAME_LENGTH, stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Remove newline

    // Search across all teams
    for (int i = 0; i < team_count; i++) {
        team_t *team = &teams[i]; //array to go through each element
        for (int j = 0; j < team->active_size; j++) {
            // Use strcasecmp for case-insensitive comparison
            if (strcasecmp(team->players[j].name, search_name) == 0) {
                printf("Player found in club %s.\n", team->name);
                printf("Current details:\n"); 
                printf("  Name: %s\n  Kit Number: %d\n  Position: %s\n  DOB: %d/%d/%d\n",
                       team->players[j].name, team->players[j].kit_number,
                       team->players[j].position, team->players[j].day,
                       team->players[j].month, team->players[j].year); //shows all the details of the player

                printf("Enter new kit number: ");
                scanf("%d", &team->players[j].kit_number); //entering new kit number
                while (getchar() != '\n'); // Clear newline after scanf
                printf("Enter new position: "); //entering new position
                fgets(team->players[j].position, NAME_LENGTH, stdin);
                team->players[j].position[strcspn(team->players[j].position, "\n")] = '\0'; // Remove newline
                printf("Details updated successfully.\n");
                return;
            }
        }
    }
    printf("Player not found.\n"); //if there is no player, shows not found
}

// Display statistics for all clubs
void display_club_statistics(team_t teams[], int team_count) {
    if (team_count == 0) {
        handle_error("No clubs are enrolled yet.");
        return;
    }

    for (int i = 0; i < team_count; i++) {
        printf("\nClub: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].active_size);

        for (int j = 0; j < teams[i].active_size; j++) {   //goes through all the teams and shows the player number
            player_t *player = &teams[i].players[j];
            printf("  Player: %s | Kit: %d | Position: %s | DOB: %d/%d/%d\n",
                   player->name, player->kit_number,
                   player->position, player->day, player->month, player->year); 
        }
    }
}

// Handles errors and prints a message
void handle_error(const char *message) {
    printf("Error: %s\n", message);
}
