/*************************************************************************
 *  Name: hangman.c                                                      *
 *  Purpose: Play hangman in terminal.                                   *
 *  Date: 12/08/2021                                                     *
 *  Author: L. G. Costa                                                  *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void allocate_memory();
void ask_word_and_tip();
void create_body();
void show_hanged_man();
void show_lines();
int menu();
void try_word();
void try_letter();

typedef struct {
    char inputed_word[20];
    char tip[256];
    char lines[20];
    char *man_hanged[6];
    char letter_wrong[6];
    int parts_resting;
    int win;
}dados;

dados game;

int main() {
    int option;
    int play = 1;

    allocate_memory();
    ask_word_and_tip();
    create_body();
    game.parts_resting = 5;
    
    do {
        do{
                system("clear");
                printf("------------\tTHE HANGED MAN\t------------\n\n\t\t%s", game.tip);
                printf("\n\n\t\tErros: ");
                for (int i = 5; i >= game.parts_resting; i--) {
                    printf("%c   ",game.letter_wrong[i] );
                }
                show_hanged_man();
                show_lines();

                option = menu();
                switch(option) {
                    case 1:
                        try_word();
                        break;
                    case 2:
                        try_letter();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Digite uma opção valída por favor!");
                }


            }while(option != 0 && game.win != 1 && game.parts_resting != -1);

            if (game.parts_resting == -1) {
                printf("\nInfelizmente você perdeu jogador 2 :(\n");
                sleep(3);
            }
        printf("\nVocê deseja jogar novamente? \t[1] Sim [0] Não\n--> ");
        scanf(" %d", &play);
        
        if (play == 1) {
            game.parts_resting = 5;
            game.win = 0;
            system("clear");
            while((play = getchar()) != '\n' && play != EOF);
            play = 1;
            ask_word_and_tip();
        }

    }while(play == 1);
    
    return 0;

}

void allocate_memory() {
    
    for (int i = 0; i < 5; i++) {
        game.man_hanged[i] = malloc(50);
    }

    system("clear");
}

void ask_word_and_tip() {
    printf("--------\tTHE HANGED MAN GAME\t--------");
    printf("\n\nJogador 1 - Digite a palavra: ");
    scanf("%[^\n]s", game.inputed_word);
    printf("Jogador 1 - Digite a dica: ");
    scanf(" %[^\n]s", game.tip);
}

void create_body() {
    game.man_hanged[5] = "\n\n|___\n|  O\n| /|\\\n| / \\   ";
    game.man_hanged[4] = "\n\n|___\n|  O\n| /|\\\n| /      ";
    game.man_hanged[3] = "\n\n|___\n|  O\n| /|\\\n|        ";
    game.man_hanged[2] = "\n\n|___\n|  O\n| /|\n|          ";
    game.man_hanged[1] = "\n\n|___\n|  O\n|  |\n|          ";
    game.man_hanged[0] = "\n\n|___\n|  O\n|   \n|          ";
}

void show_hanged_man() {
    printf("%s", game.man_hanged[game.parts_resting]);
}

void show_lines() {
    
    for(int i = 0; i < strlen(game.inputed_word); i++){
        if (game.lines[i] != game.inputed_word[i]){
            if (game.inputed_word[i] == ' '){
                game.lines[i] = ' ';
            }
            else {
                game.lines[i] = '_';
            }
        }
        if (game.lines[i] == ' '){
            printf("* ");
        }
        else {
            printf("%c ", game.lines[i]);
        }
    }


}

int menu(){
    int what_to_do;
    printf("\n\n[1] Digitar a palavra\n[2] Digitar uma letra\n[0] Sair/Desistir\n--> ");
    scanf(" %d", &what_to_do);
    return what_to_do;
}

void try_word() {
    char try_word[20];
    printf("\nJogador 2 - Digite a palavra: ");
    scanf(" %[^\n]s", try_word);

    if (strcmp(try_word, game.inputed_word) == 0){
        printf("Parabéns jogador 2 você ganhou!!!!\n");
        sleep(3);
        game.win = 1;
    }
    else {
        game.parts_resting -= 1;
    }
}

void try_letter() {
    char try_letter;
    int count = 0;
    printf("\nJogador 2 - Digite a letra: ");
    scanf(" %[^\n]c", &try_letter);

    for (int i = 0; i < strlen(game.inputed_word); i++) {
        if (game.inputed_word[i] == try_letter) {
            game.lines[i] = try_letter;
        }
        else {
            count++;
        }
    }

    if (count == strlen(game.inputed_word)) {
        game.parts_resting -= 1;
        game.letter_wrong[game.parts_resting] = try_letter;
    }

    if (strcmp(game.lines, game.inputed_word) == 0){
        printf("Parabéns jogador 2 você ganhou!!!!\n");
        sleep(3);
        game.win = 1;
    }
}