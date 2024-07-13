#include <stdio.h>
#include <string.h>

struct Nombre {
    char nombre[50];
    char apellidos[50];
};

struct Estudiante {
    struct Nombre nombre_completo;
    int matricula;
    int carrera;
};

void imprimirEstudiante(struct Estudiante estudiante) {
    printf("Nombre: %s %s\n", estudiante.nombre_completo.nombre, estudiante.nombre_completo.apellidos);
    printf("Matricula: %d\n", estudiante.matricula);
    printf("Carrera: %d\n\n", estudiante.carrera);
}

int main() {
    FILE *archivo;
    archivo = fopen("estudiantes.txt", "w"); // Abre el archivo para escritura

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    struct Estudiante estudiantes[50];
    int numEstudiantes = 0; // Contador de estudiantes ingresados

    do {
        int opcion;
        printf("Opciones:\n");
        printf("1. Ingresar estudiantes\n");
        printf("2. Editar estudiante\n");
        printf("3. Eliminar estudiante\n");
        printf("4. Mostrar todos los estudiantes\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        int numIngresar;
        int matriculaEditar;
        int matriculaEliminar;

        switch (opcion) {
            case 1:
                printf("Cuantos estudiantes deseas ingresar en esta iteracion (maximo 50)? ");
                scanf("%d", &numIngresar);
                if (numIngresar > 0 && numIngresar <= 50 - numEstudiantes) {
                    for (int i = numEstudiantes; i < numEstudiantes + numIngresar; i++) {
                        printf("Estudiante #%d\n", i + 1);

                        int matriculaIngresada;
                        printf("Matricula: ");
                        scanf("%d", &matriculaIngresada);

                        // Verificar si la matricula ya existe
                        int matriculaDuplicada = 0;
                        for (int j = 0; j < numEstudiantes; j++) {
                            if (estudiantes[j].matricula == matriculaIngresada) {
                                matriculaDuplicada = 1;
                                break;
                            }
                        }

                        if (matriculaDuplicada) {
                            printf("La matricula ingresada ya existe. Introduce una matricula diferente.\n");
                        } else {
                            // Continuar ingresando los demas datos
                            estudiantes[i].matricula = matriculaIngresada;
                            fflush(stdin);
                            printf("Nombre: ");
                            scanf("%s", estudiantes[i].nombre_completo.nombre);
                            printf("Apellidos: ");
                            scanf("%s", estudiantes[i].nombre_completo.apellidos);
                            fflush(stdin);
                            printf("Carrera: 01 Electronica, 02 Mecatronica, 03 Informatica (Ingresa solo el numero): ");
                            scanf("%d", &estudiantes[i].carrera);

                            fprintf(archivo, "Nombre: %s %s\n", estudiantes[i].nombre_completo.nombre, estudiantes[i].nombre_completo.apellidos);
                            fprintf(archivo, "Matricula: %d\n", estudiantes[i].matricula);
                            fprintf(archivo, "Carrera: %d\n\n", estudiantes[i].carrera);
                        }
                    }
                    numEstudiantes += numIngresar;
                } else {
                    printf("Numero invalido de estudiantes. Por favor, ingresa un valor entre 1 y %d.\n", 50 - numEstudiantes);
                }
                break;
            case 2:
                printf("Ingresa la matricula del estudiante que deseas editar: ");
                scanf("%d", &matriculaEditar);

                int indiceEditar = -1;
                for (int i = 0; i < numEstudiantes; i++) {
                    if (estudiantes[i].matricula == matriculaEditar) {
                        indiceEditar = i;
                        break;
                    }
                }

                if (indiceEditar != -1) {
                    printf("Editando estudiante #%d\n", indiceEditar + 1);
                    imprimirEstudiante(estudiantes[indiceEditar]);

                    printf("Nuevo nombre: ");
                    scanf("%s", estudiantes[indiceEditar].nombre_completo.nombre);
                    printf("Nuevo apellidos: ");
                    scanf("%s", estudiantes[indiceEditar].nombre_completo.apellidos);
                    fflush(stdin);
                    printf("Nueva matricula: ");
                    scanf("%d", &estudiantes[indiceEditar].matricula);
                    fflush(stdin);
                    printf("Nueva carrera (01 Electronica, 02 Mecatronica, 03 Informatica): ");
                    scanf("%d", &estudiantes[indiceEditar].carrera);

                    // Actualizar los datos en el archivo
                    fclose(archivo);
                    archivo = fopen("estudiantes.txt", "w");
                    for (int i = 0; i < numEstudiantes; i++) {
                        fprintf(archivo, "Nombre: %s %s\n", estudiantes[i].nombre_completo.nombre, estudiantes[i].nombre_completo.apellidos);
                        fprintf(archivo, "Matricula: %d\n", estudiantes[i].matricula);
                        fprintf(archivo, "Carrera: %d\n\n", estudiantes[i].carrera);
                    }
                    printf("Estudiante editado con exito.\n");
                } else {
                    printf("Estudiante no encontrado.\n");
                }
                break;
            case 3:
                printf("Ingresa la matricula del estudiante que deseas eliminar: ");
                scanf("%d", &matriculaEliminar);
                int indiceEliminar = -1;
                for (int i = 0; i < numEstudiantes; i++) {
                    if (estudiantes[i].matricula == matriculaEliminar) {
                        indiceEliminar = i;
                        break;
                    }
                }

                if (indiceEliminar != -1) {
                    for (int i = indiceEliminar; i < numEstudiantes - 1; i++) {
                        estudiantes[i] = estudiantes[i + 1];
                    }

                    numEstudiantes--;

                    printf("Estudiante eliminado con exito.\n");

                    // Reescribir el archivo con los registros actualizados
                    fclose(archivo);
                    archivo = fopen("estudiantes.txt", "w");
                    for (int i = 0; i < numEstudiantes; i++) {
                        fprintf(archivo, "Nombre: %s %s\n", estudiantes[i].nombre_completo.nombre, estudiantes[i].nombre_completo.apellidos);
                        fprintf(archivo, "Matricula: %d\n", estudiantes[i].matricula);
                        fprintf(archivo, "Carrera: %d\n\n", estudiantes[i].carrera);
                    }
                } else {
                    printf("Estudiante no encontrado.\n");
                }
                break;
            case 4:
                printf("Lista de todos los estudiantes:\n");
                for (int i = 0; i < numEstudiantes; i++) {
                    printf("Estudiante #%d\n", i + 1);
                    imprimirEstudiante(estudiantes[i]);
                }
                break;
            case 5:
                break; // Salir del programa
            default:
                printf("Opcion invalida. Por favor, selecciona una opcion valida.\n");
        }
        puts("");
    } while (numEstudiantes < 50);

    fclose(archivo);

    printf("Datos de estudiantes guardados en el archivo 'estudiantes.txt'.\n");

    return 0;
}
