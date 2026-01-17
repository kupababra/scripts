/* abrakadabra.c Gentoo Linux - updater
   Prosty zautomatyzowany update systemu */
/* Autor: id3fix@retro-technology.pl */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOG_FILE "/var/log/gentoo_update.log"

void run_cmd(const char *cmd) {
    char full_cmd[512];
    snprintf(full_cmd, sizeof(full_cmd), "%s >> %s 2>&1", cmd, LOG_FILE);
    printf("[INFO] %s\n", cmd);
    int status = system(full_cmd);
    if (status != 0) {
        printf("[BŁĄD] Komenda zakończyła się błędem. Sprawdź log: %s\n", LOG_FILE);
    }
}

int command_exists(const char *cmd) {
    char path[256];
    snprintf(path, sizeof(path), "/bin/sh -c 'command -v %s >/dev/null 2>&1'", cmd);
    return system(path) == 0;
}

int main() {
    printf("==========================================\n");
    printf("     Gentoo System Update Utility (C)     \n");
    printf("==========================================\n");

    if (geteuid() != 0) {
        fprintf(stderr, "[BŁĄD] Ten program musi być uruchomiony jako root.\n");
        return 1;
    }

    printf("[✓] Rozpoczynam aktualizację Gentoo\n");
    printf("[→] Wszystkie operacje są logowane do: %s\n\n", LOG_FILE);

    run_cmd("emerge --sync");
    run_cmd("emerge -avuDN @world");
    run_cmd("emerge --depclean");

    if (command_exists("revdep-rebuild")) {
        printf("\nCzy chcesz uruchomić revdep-rebuild? [T/n]: ");
        char c;
        scanf(" %c", &c);
        if (c != 'n' && c != 'N') {
            run_cmd("revdep-rebuild");
        }
    }

    // Bootloader update
    printf("\nCzy chcesz zaktualizować GRUB lub LILO? [t/N]: ");
    char boot;
    scanf(" %c", &boot);

    if (boot == 't' || boot == 'T') {
        if (access("/usr/sbin/grub-mkconfig", X_OK) == 0) {
            run_cmd("grub-mkconfig -o /boot/grub/grub.cfg");
        } else if (access("/sbin/lilo", X_OK) == 0) {
            run_cmd("lilo -v");
        } else {
            printf("[INFO] Nie znaleziono GRUB ani LILO.\n");
        }
    }

    printf("\n[✓] Aktualizacja zakończona.\nSprawdź szczegóły w logu: %s\n", LOG_FILE);
    return 0;
}

