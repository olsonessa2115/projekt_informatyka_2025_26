Olivier Dułak 204004

Scenariusz rozgrywki

Po uruchomieniu programu możemy sobie wybrać strzałkami czy chcemy zacząć nową grę, wczytać starą, czy wyjść. Jak wybierzemy start, to gra resetuje planszę i zaczynamy odbijać piłkę. Przez cały czas sterujemy paletką na dole i staramy się zbić cegły wiszące u góry. W każdej chwili można wcisnąć pauzę albo zapisać grę, jeśli musimy kończyć. Jak piłka nam spadnie, to nie trzeba resetować całej aplikacji – wyskakuje komunikat o przegranej i wystarczy wcisnąć Enter, żeby gra sama przygotowała nową rundę i można było próbować dalej.

Sposób uruchomienia

Żeby gra ruszyła, potrzebne jest środowisko obsługujące C++, na przykład Visual Studio, oraz poprawnie podpięta biblioteka SFML. Najważniejszą rzeczą, o której trzeba pamiętać przy uruchamianiu, jest plik z czcionką "arial.ttf". Musi on leżeć w tym samym folderze co plik wykonywalny gry (.exe). Bez tej czcionki gra się po prostu nie włączy.

Opis funkcjonalności

W projekcie udało mi się zaimplementować kilka fajnych mechanik. Przede wszystkim działa pełne menu, gdzie opcje podświetlają się na czerwono, więc widać, co wybieramy. Zrobiłem też system zapisu i odczytu, który zrzuca stan gry do pliku tekstowego (savegame.txt), dzięki czemu nie tracimy postępów po wyłączeniu okna. Same cegiełki uderzyć kilka razy, a one zmieniają kolor, żeby pokazać, że są uszkodzone. Do tego dochodzi cała fizyka piłki, która odbija się od ścian i paletki w zależności od tego, w który bok uderzy. Całość jest podzielona na stany, więc gra płynnie przechodzi między menu, rozgrywką a ekranem końcowym.
