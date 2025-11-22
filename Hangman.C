#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEVELS 5
#define MAX_INPUT 200
#define MAX_CLUE 256

// Struktur menyimpan clue dan jawaban
typedef struct {
    char clue[MAX_CLUE];
    char answer[MAX_CLUE];
} Level;

// Normalisasi teks: huruf kecil dan spasi dihapus
void normalize(const char *src, char *dst) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
        if (!isspace((unsigned char)src[i])) {
            dst[j++] = tolower((unsigned char)src[i]);
        }
    }
    dst[j] = '\0';
}

int main() {
    Level levels[MAX_LEVELS] = {
        {"Aku selalu ada di pohon, tapi aku bukan buah. Aku hijau… kecuali kalau aku sedang \"bermasalah\".", "daun"},
        {"Aku bisa berpikir, bisa jatuh cinta, bisa patah hati, tapi aku bukan karakter film — aku nyata.", "manusia"},
        {"Aku terkenal di seluruh dunia hanya karena tersenyum sedikit, tapi aku tidak pernah bilang apa-apa.", "mona lisa"},
        {"Aku sangat tinggi sampai orang bangga menaklukkanku, tapi aku tetap di tempat — diam saja.", "mount everest"},
        {"Semua orang pernah punya aku, tapi tidak semua mau mengakuinya.", "mantan"}
    };

    int lives = 3; // nyawa awal
    int level = 0;
    char input[MAX_INPUT], normInput[MAX_INPUT], normAns[MAX_INPUT];

    printf("=== GAME TEBAK KATA ===\n");
    printf("Ada 5 level. Kamu punya 3 nyawa.\n");
    printf("Setiap berhasil naik level → bonus +1 nyawa.\n");
    printf("Jawaban tidak sensitif huruf besar/kecil, spasi diabaikan.\n\n");

    while (level < MAX_LEVELS && lives > 0) {
        printf("Level %d\n", level + 1);
        printf("Clue: %s\n", levels[level].clue);
        printf("Tebakan: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error. Keluar...\n");
            return 1;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        normalize(input, normInput);
        normalize(levels[level].answer, normAns);

        if (strlen(normInput) == 0) {
            printf("Tidak boleh kosong. Coba lagi!\n\n");
            continue;
        }

        if (strcmp(normInput, normAns) == 0) {
            printf("Benar! Jawaban: %s\n", levels[level].answer);
            level++;
            lives++;  // BONUS
            printf("Bonus nyawa! → Nyawa sekarang: %d\n\n", lives);
        } else {
            lives--;
            if (lives > 0) {
                printf("Salah. Nyawa tersisa: %d\n\n", lives);
            } else {
                printf("Salah. Nyawa tersisa: 0\n");
                printf("GAME OVER! Jawaban yang benar: %s\n\n", levels[level].answer);
            }
        }
    }

    if (level == MAX_LEVELS)
        printf("SELAMAT! Kamu menyelesaikan semua level!\n");
    else if (lives == 0)
        printf("Coba lagi lain waktu.\n");

    return 0;
}
