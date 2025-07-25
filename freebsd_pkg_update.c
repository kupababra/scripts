/* Prosty updater pakietów do systemu FreeBSD*  Unix 
   Logowanie nastepuje do /var/log/ 
   Autor: bofh@retro-technology.pl 
   Kompilacja: cc -o freebsd_pkg_update freebsd_pkg_update.c 
   Program wymaga uprawnień administratora:
   Uruchomienie:
   doas ./freebsd_pkg_update lub sudo ./freebsd_pkg_update */ 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOG_FILE "/var/log/freebsd_pkg_update.log"

void run_command(const char *cmd) {
    char full_cmd[512];
    snprintf(full_cmd, sizeof(full_cmd), "%s >> %s 2>&1", cmd, LOG_FILE);
    printf("[INFO] Uruchamiam: %s\n", cmd);
    int ret = system(full_cmd);
    if (ret != 0) {
        printf("[BŁĄD] Komenda '%s' zakończyła się błędem. Sprawdź log: %s\n", cmd, LOG_FILE);
    }
}

int main() {
    printf("======================================\n");
    printf("  FreeBSD Packages Update Utility\n");
    printf("======================================\n");

    if (geteuid() != 0) {
        fprintf(stderr, "[BŁĄD] Program musi być uruchomiony jako root.\n");
        return 1;
    }

    printf("[✓] Aktualizacja listy pakietów...\n");
    run_command("pkg update");

    printf("[✓] Aktualizacja zainstalowanych pakietów...\n");
    run_command("pkg upgrade -y");

    printf("\n[✓] Aktualizacja pakietów zakończona. Sprawdź log: %s\n", LOG_FILE);

    return 0;
}

