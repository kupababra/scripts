/*
Rootkit checker v1 alpha by id3fix@retro-technology.pl
- dla systemu Linux (np. Gentoo, Debian, FreeBSD z procfs itp.).
Ten program NIE usuwa niczego, tylko:
- szuka podejrzanych plików w typowych miejscach: /dev, /lib, /etc, /tmp, /usr
- wypisuje ukryte procesy (np. nieobecne w ps ale widoczne w /proc)
- sprawdza znane biblioteki i pliki często podmieniane przez rootkity

Użycie:
cc -o rootkit_checker rootkit_checker.c
doas ./rootkit_checker
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>

void check_suspicious_files() {
    const char *suspicious_paths[] = {
        "/dev/.lib", "/dev/.udev", "/dev/.tmp", "/dev/.rootkit", // add and change 
        "/etc/rc.d/init.d/.../", "/usr/lib/.bkit", "/lib/.lib", // new hacks
        "/tmp/.../", "/usr/bin/ssh2", "/usr/sbin/in.telnetd", NULL // of course
    };

    printf("== Sprawdzanie podejrzanych plików ==\n");

    for (int i = 0; suspicious_paths[i] != NULL; i++) {
        if (access(suspicious_paths[i], F_OK) == 0) {
            printf("[!] Znaleziono podejrzany plik: %s\n", suspicious_paths[i]);
        }
    }
}

int is_numeric(const char *str) {
    while (*str) {
        if (!isdigit(*str++)) return 0;
    }
    return 1;
}

void list_hidden_processes() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("Nie można otworzyć /proc");
        return;
    }

    struct dirent *entry;
    printf("\n== Szukanie ukrytych procesów ==\n");

    while ((entry = readdir(proc)) != NULL) {
        if (entry->d_type == DT_DIR && is_numeric(entry->d_name)) {
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/cmdline", entry->d_name);
            FILE *cmdline = fopen(path, "r");

            if (cmdline) {
                char cmd[256];
                fread(cmd, 1, sizeof(cmd), cmdline);
                if (strlen(cmd) == 0) {
                    printf("[!] Ukryty lub pusty proces PID: %s\n", entry->d_name);
                }
                fclose(cmdline);
            }
        }
    }

    closedir(proc);
}

void check_ld_preload() {
    printf("\n== Sprawdzanie zmiennej środowiskowej LD_PRELOAD ==\n");
    char *ld_preload = getenv("LD_PRELOAD");
    if (ld_preload && strlen(ld_preload) > 0) {
        printf("[!] LD_PRELOAD ustawione: %s\n", ld_preload);
    } else {
        printf("[OK] LD_PRELOAD nie jest ustawione.\n");
    }
}

int main() {
    printf("=========================================\n");
    printf("   Rootkit Checker dla systemów Linux/BSD\n");
    printf("=========================================\n");

    if (geteuid() != 0) {
        fprintf(stderr, "[BŁĄD] Uruchom program jako root.\n");
        return 1;
    }

    check_suspicious_files();
    list_hidden_processes();
    check_ld_preload();

    printf("\n[✓] Skanowanie zakończone.\n");

    return 0;
}

