#include <stdio.h>
#include <string.h>

// Definicion de la estructura Libro
struct Libro {
    int id; // Numero de identificador unico
    char titulo[100];
    char autores[100];
    char editorial[50];
    int anio_publicacion;
    float precio;
    int num_ejemplares;
};

// Funcion para editar un libro por su ID
void editarLibro(struct Libro biblioteca[], int num_libros, int id) {
    for (int i = 0; i < num_libros; i++) {
        if (biblioteca[i].id == id) {
            printf("Ingrese los nuevos datos para el libro #%d:\n", id);
            printf("Titulo: ");
            scanf("%s", biblioteca[i].titulo);
            printf("Autores: ");
            scanf("%s", biblioteca[i].autores);
            printf("Editorial: ");
            scanf("%s", biblioteca[i].editorial);
            printf("Anio de publicacion: ");
            scanf("%d", &biblioteca[i].anio_publicacion);
            printf("Precio: ");
            scanf("%f", &biblioteca[i].precio);
            printf("Numero de ejemplares: ");
            scanf("%d", &biblioteca[i].num_ejemplares);
            printf("Libro editado con exito.\n");
            return;
        }
    }
    printf("No se encontro un libro con el ID especificado.\n");
}

// Funcion para mostrar libros por anio
void mostrarLibrosPorAnio(struct Libro biblioteca[], int num_libros, int anio) {
    printf("Libros publicados en el anio %d:\n", anio);
    for (int i = 0; i < num_libros; i++) {
        if (biblioteca[i].anio_publicacion == anio) {
            printf("ID: %d, Titulo: %s, Autores: %s, Editorial: %s, Precio: %.2f, Ejemplares: %d\n",
                   biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autores, biblioteca[i].editorial,
                   biblioteca[i].precio, biblioteca[i].num_ejemplares);
        }
    }
}

// Funcion para mostrar libros con menos de 2 ejemplares
void mostrarLibrosConMenosEjemplares(struct Libro biblioteca[], int num_libros, int limite_ejemplares) {
    printf("Libros con menos de %d ejemplares:\n", limite_ejemplares);
    for (int i = 0; i < num_libros; i++) {
        if (biblioteca[i].num_ejemplares < limite_ejemplares) {
            printf("ID: %d, Titulo: %s, Autores: %s, Editorial: %s, Precio: %.2f, Ejemplares: %d\n",
                   biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autores, biblioteca[i].editorial,
                   biblioteca[i].precio, biblioteca[i].num_ejemplares);
        }
    }
}

// Funcion para mostrar todos los libros en la biblioteca
void mostrarTodosLosLibros(struct Libro biblioteca[], int num_libros) {
    printf("Todos los libros en la biblioteca:\n");
    for (int i = 0; i < num_libros; i++) {
        printf("ID: %d, Titulo: %s, Autores: %s, Editorial: %s, Anio de publicacion: %d, Precio: %.2f, Ejemplares: %d\n",
               biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autores, biblioteca[i].editorial,
               biblioteca[i].anio_publicacion, biblioteca[i].precio, biblioteca[i].num_ejemplares);
    }
}

// Funcion para guardar la biblioteca en un archivo
void guardarBiblioteca(struct Libro biblioteca[], int num_libros) {
    FILE *archivo = fopen("Base de datos de la biblioteca.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    for (int i = 0; i < num_libros; i++) {
        fprintf(archivo, "ID: %d\n", biblioteca[i].id);
        fprintf(archivo, "Titulo: %s\n", biblioteca[i].titulo);
        fprintf(archivo, "Autores: %s\n", biblioteca[i].autores);
        fprintf(archivo, "Editorial: %s\n", biblioteca[i].editorial);
        fprintf(archivo, "Anio de publicacion: %d\n", biblioteca[i].anio_publicacion);
        fprintf(archivo, "Precio: %.2f\n", biblioteca[i].precio);
        fprintf(archivo, "Numero de ejemplares: %d\n", biblioteca[i].num_ejemplares);
        fprintf(archivo, "\n");
    }

    fclose(archivo);
    printf("Biblioteca guardada en 'Base de datos de la biblioteca.txt'.\n");
}

// Funcion para cargar la biblioteca desde un archivo
int cargarBiblioteca(struct Libro biblioteca[]) {
    FILE *archivo = fopen("Base de datos de la biblioteca.txt", "r");
    if (archivo == NULL) {
        printf("El archivo no existe o no se puede abrir.\n");
        return 0;
    }

    int num_libros = 0;
    while (fscanf(archivo, "ID: %d\n", &biblioteca[num_libros].id) != EOF) {
        fscanf(archivo, "Titulo: %[^\n]\n", biblioteca[num_libros].titulo);
        fscanf(archivo, "Autores: %[^\n]\n", biblioteca[num_libros].autores);
        fscanf(archivo, "Editorial: %[^\n]\n", biblioteca[num_libros].editorial);
        fscanf(archivo, "Anio de publicacion: %d\n", &biblioteca[num_libros].anio_publicacion);
        fscanf(archivo, "Precio: %f\n", &biblioteca[num_libros].precio);
        fscanf(archivo, "Numero de ejemplares: %d\n", &biblioteca[num_libros].num_ejemplares);
        num_libros++;
    }

    fclose(archivo);
    printf("Biblioteca cargada desde 'Base de datos de la biblioteca.txt'.\n\n");
    return num_libros;
}

int main() {
    struct Libro biblioteca[50];
    int num_libros = 0;
    int next_id = 1;
    int cantidad_ingresar; // Declarar la variable al principio
    int id_editar;
    int anio_mostrar;
    int limite_ejemplares;
    int opcion;

    // Cargar la biblioteca desde el archivo al inicio
    num_libros = cargarBiblioteca(biblioteca);

    do {
        printf("Menu:\n");
        printf("1. Agregar libros\n");
        printf("2. Editar libros\n");
        printf("3. Mostrar libros por anio\n");
        printf("4. Mostrar libros con menos de 2 ejemplares\n");
        printf("5. Mostrar todos los libros\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Cuantos libros deseas ingresar en esta iteracion? ");
                scanf("%d", &cantidad_ingresar);

                for (int i = 0; i < cantidad_ingresar; i++) {
                    if (num_libros < 50) {
                        printf("Ingrese los datos del libro #%d:\n", next_id);
                        biblioteca[num_libros].id = next_id;
                        printf("Titulo: ");
                        scanf("%s", biblioteca[num_libros].titulo);
                        printf("Autores: ");
                        scanf("%s", biblioteca[num_libros].autores);
                        printf("Editorial: ");
                        scanf("%s", biblioteca[num_libros].editorial);
                        printf("Anio de publicacion: ");
                        scanf("%d", &biblioteca[num_libros].anio_publicacion);
                        printf("Precio: ");
                        scanf("%f", &biblioteca[num_libros].precio);
                        printf("Numero de ejemplares: ");
                        scanf("%d", &biblioteca[num_libros].num_ejemplares);

                        num_libros++;
                        next_id++;
                        puts("");
                    } else {
                        printf("No se pueden agregar mas libros, la biblioteca esta llena.\n");
                        puts("");
                        break;
                    }
                }
                puts("");
                break;

            case 2:
                printf("Ingrese el ID del libro que desea editar: ");
                scanf("%d", &id_editar);
                editarLibro(biblioteca, num_libros, id_editar);
                puts("");
                break;

            case 3:
                printf("Ingrese el anio de publicacion para mostrar los libros: ");
                scanf("%d", &anio_mostrar);
                mostrarLibrosPorAnio(biblioteca, num_libros, anio_mostrar);
                puts("");
                break;

            case 4:
                printf("Ingrese el limite de ejemplares para mostrar los libros: ");
                scanf("%d", &limite_ejemplares);
                mostrarLibrosConMenosEjemplares(biblioteca, num_libros, limite_ejemplares);
                puts("");
                break;

            case 5:
                mostrarTodosLosLibros(biblioteca, num_libros);
                puts("");
                break;

            case 6:
                // Guardar la biblioteca en un archivo antes de salir
                guardarBiblioteca(biblioteca, num_libros);
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}
