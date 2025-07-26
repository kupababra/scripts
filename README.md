
# 🧰 Zestaw terminalowych narzędzi systemowych (Linux / FreeBSD)

Zestaw czterech lekkich, terminalowych narzędzi systemowych w C i Bash, działających na systemach **Linux** i **FreeBSD**.  
Każdy z plików pełni konkretną funkcję administracyjną — od aktualizacji pakietów po sprawdzanie rootkitów.

---

## 🔹 abrakadabra.c

**Opis:**  
Prosty program typu "sekretne polecenie" – wykonuje ukrytą operację systemową po spełnieniu warunku (np. hasła, argumentu, specjalnego trybu debug).  
Może służyć jako baza pod narzędzia diagnostyczne, hasłowane lub testowe.

**Skompiluj:**  
```bash
gcc abrakadabra.c -o abrakadabra
```

---

## 🔹 freebsd_pkg_update.c

**Opis:**  
Małe narzędzie do aktualizacji pakietów w systemie FreeBSD (`pkg upgrade`, `pkg update`).  
Automatyzuje proces i wyświetla prosty pasek postępu (można rozbudować o ncurses).

**Platforma:** FreeBSD

**Skompiluj:**  
```bash
gcc freebsd_pkg_update.c -o pkgupdate
```

---

## 🔹 rootkit_checker.c

**Opis:**  
Podstawowy skaner systemowy – wykrywa podejrzane procesy, pliki, lub modyfikacje binarek systemowych.  
Nie korzysta z zewnętrznych bibliotek – czysty ANSI C.

**Platforma:** Linux

**Skompiluj:**  
```bash
gcc rootkit_checker.c -o rkcheck
```

---

## 🔹 szukaj.sh

**Opis:**  
Skrypt Bash do wyszukiwania plików, fraz lub konfiguracji w systemie.  
Może być używany do przeszukiwania katalogów systemowych, np. `/etc`.

**Platforma:** Linux / FreeBSD

**Uruchomienie:**  
```bash
chmod +x szukaj.sh
./szukaj.sh "nazwa" /etc
```

---

## 📌 Uwagi dodatkowe

- Kompilacja wymaga `gcc` lub `clang`
- Niektóre narzędzia mogą wymagać uruchomienia jako `root`
- Skrypt `freebsd_pkg_update.c` działa tylko na FreeBSD z `pkg(8)`
- `rootkit_checker.c` może być bazą pod większy projekt audytu bezpieczeństwa

---

## 📄 Licencja

MIT – używaj, ucz się i modyfikuj swobodnie.
