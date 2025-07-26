# 🧙‍♂️ Systemowe Narzędzia CLI (Linux / FreeBSD)

Zestaw pięciu lekkich, terminalowych narzędzi systemowych w C i Bash, działających na systemach **Linux** i **FreeBSD**. 
Każdy z plików pełni konkretną funkcję administracyjną — od aktualizacji pakietów po sprawdzanie rootkitów.

---

## 🗂️ Pliki

1. abrakadabra.c
**Opis:**  
Prosty program typu "sekretne polecenie" – wykonuje ukrytą operację systemową po spełnieniu warunku (np. hasła, argumentu, specjalnego trybu debug).  
Może służyć jako baza pod narzędzia diagnostyczne, hasłowane lub testowe.  
**Platforma:** Linux / FreeBSD  
**Skompiluj:**  
```bash
gcc abrakadabra.c -o abrakadabra

2. freebsd_pkg_update.c
Opis:
Małe narzędzie do aktualizacji pakietów w systemie FreeBSD (pkg upgrade, pkg update).
Automatyzuje proces i wyświetla prosty pasek postępu (można rozbudować o ncurses).
Platforma: FreeBSD
Skompiluj:
gcc freebsd_pkg_update.c -o pkgupdate

3. rootkit_checker.c
Opis:
Podstawowy skaner systemowy – wykrywa podejrzane procesy, pliki, lub modyfikacje binarek systemowych.
Nie korzysta z zewnętrznych bibliotek – czysty ANSI C.
Platforma: Linux
Skompiluj:
gcc rootkit_checker.c -o rkchecksd_pkg_update.c -o pkgupdate

4. szukaj.sh
Opis:
Skrypt Bash do wyszukiwania plików, fraz lub konfiguracji w systemie.
Platforma: Linux / FreeBSD
Uruchomienie:
chmod +x szukaj.sh
./szukaj.sh "nazwa" /etc

