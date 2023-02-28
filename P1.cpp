#include <ncurses.h>
#include <string>
#include <iostream>
#include <fstream>

int main(){
    
    
    initscr();// Inicia ña lib ncurses
    cbreak();// Te permite escribir en elnuevo bufer que hemos lanzado 
    noecho();// Nos desactiva  los caracteres integrados por el usuario en la pantalla
    keypad(stdscr, TRUE);// Nos permite usar las flechitas

    // Configurar la ventana
    int height, width;// dos variables
    getmaxyx(stdscr, height, width);// el stdscr es un puentero que apunta al buffer
    WINDOW* editor_window = newwin(height/2, width/2, 0, 0);// crea la venta donde se va escribir y lo otro el tamaño de dicha ventana
    scrollok(editor_window, TRUE);// Para qeu se pueda mover la ventana

    // Ciclo principal
    std::string input;
    int hola = getch(); //LA FUNCION GETCH ESPERA QUE EL USUARIO PRESIONE UNA TECLA Y EL DEVUELVE EL CODIGO DE LA TECLA PRESIONADA
    while (hola != KEY_F(1))// Es una consastante que tiene la lib ncurses, en esta en especifico se refiere a la tecla F1 de esta forma para por asi decirlo saldriamos del editor
    {
        // Procesar entrada de teclado
        switch (hola)
        {
            case KEY_BACKSPACE:// esto pare eliminar
                if (!input.empty()) {input.pop_back();}// ! esto no sabia como  hacerlo xd, me lo dio chat gpt :)
                break;
            case KEY_ENTER:// esto para salto de linea
                input += '\n';
                break;
            default:// esto agrega el caracter presionado  a  lacadena input convirtiendolo  en un char con el  static noseque
                input += static_cast<char>(hola);
        }

        // Actualizar la ventana del editor
        werase(editor_window);// Función que borra el contenido de una ventana
        wprintw(editor_window, "%s", input.c_str());// Función que imprime una cadena de caracteres en una ventana
        wrefresh(editor_window);// Función que actualiza la pantalla con el contenido de la ventana especificada

        // Obtener el siguiente caracter de entrada
        hola = getch();
    }

    // Limpiar ncurses
    endwin();// Función que finaliza el uso de la biblioteca ncurses y devuelve la pantalla a su estado original

    // Preguntamos al usuario si quiere guardar el archivo
    std::cout << "Desea guardar el archivo? (y/n) ";
    char adios;
    std::cin >> adios;

    if (adios == 'y' || adios == 'Y') {
        // Pedimos al usuario el nombre del archivo
        std::string filename;
        std::cout << "Nombre del archivo: ";
        std::cin >> filename;

        // Guardamos el contenido en un archivo
        std::ofstream outfile(filename);
        if (outfile.is_open()) {
            outfile << input;
            outfile.close();
            std::cout << "Archivo guardado exitosamente.\n";
        } else {
            std::cerr << "Error al abrir el archivo.\n";
        }
    }

    return 0;
}
