import os

def split_data(filename):
    # Otwarcie pliku źródłowego do czytania danych
    with open(filename, 'r') as file:
        data = file.read()

    # Dzielenie danych na sekcje na podstawie wzorca 'data.'
    sections = data.split('data.')

    # Usuwanie pustych sekcji, które mogły powstać w wyniku dzielenia tekstu
    sections = [section for section in sections if section.strip()]

    # Iteracja przez każdą sekcję, przetwarzanie i zapisywanie do osobnych plików
    for section in sections:
        # Dzielenie sekcji na część danych i część 'neh'
        parts = section.split('neh:')
        data_part = parts[0].strip()
        neh_part = parts[1].strip()

        # Ekstrakcja numeru pliku z pierwszej linii części danych
        file_number = data_part.split('\n')[0].split(':')[0].strip()

        # Tworzenie nazwy pliku
        filename = path = os.path.join(os.path.dirname(__file__),"all" ,f"data_{file_number}.txt")

        # Zapisywanie danych do pliku, łącznie z odpowiednią częścią 'neh'
        with open(filename, 'w') as file:
            # Zapisuje wszystko po 'data.xxx:'
            file.write("data:\n" + data_part.split(':', 1)[1].strip() + "\n")
            file.write("neh:\n" + neh_part)

if __name__ == "__main__":
    # Podaj ścieżkę do pliku z danymi
    source_file_path = "neh_data.txt"
    split_data(source_file_path)
