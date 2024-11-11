//Autor: Jorge Chaves Montiel
//Fecha: 10-11-2024
//descripci�n: programa para ingreso de inventario e ingreso y gesti�n de pedidos
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Pieza {
    string codigo;
    string nombre;
    float costo;
    int cantidad;
    string proveedor;
    string factura;
    string cedula;
};

struct Pedido {
    string codigo;
    string codigoPieza;
    int cantidad;
    string cedulaEmpleado;
    string fecha;
    string estado;
};

string obtenerProximoCodigo(const vector<Pieza>& inventario) {
    int ultimoNumero = 0;
    for (const Pieza& p : inventario) {
        if (p.codigo.find("PE") == 0) {
            int numero = stoi(p.codigo.substr(2));
            ultimoNumero = max(ultimoNumero, numero);
        }
    }
    int nuevoNumero = ultimoNumero + 1;
    string nuevoCodigo = "PE" + string(8 - to_string(nuevoNumero).length(), '0') + to_string(nuevoNumero);

    return nuevoCodigo;
}

void agregarPiezaInventario(vector<Pieza>& inventario) {
    Pieza nuevaPieza;
    nuevaPieza.codigo = obtenerProximoCodigo(inventario);
    cout << "Ingrese el nombre de la pieza: ";
    cin.ignore();
    getline(cin, nuevaPieza.nombre);
    // Validar que el nombre de la pieza no est� vac�o
    while(nuevaPieza.nombre.empty()) {
        cout << "El nombre de la pieza no puede estar vac�o. Por favor, ingrese un nombre v�lido." << endl;
        cout << "Ingrese el nombre de la pieza: ";
        getline(cin, nuevaPieza.nombre);
    }
    // Leer el costo de la pieza y validar que sea un n�mero float o int
    bool costoValido = false;
    while (!costoValido) {
        cout << "Ingrese el costo de la pieza por unidad: ";
        if (cin >> nuevaPieza.costo) {
            costoValido = true;
        } else {
            cout << "Costo inv�lido. Por favor, ingrese un n�mero v�lido." << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        }
    }
    // Leer la cantidad de piezas y validar que sea un n�mero entero
    bool cantidadValida = false;
    while (!cantidadValida) {
        cout << "Ingrese la cantidad de piezas: ";
        string input;
        cin >> input;

        // Verificar si el input es un n�mero entero
        bool esNumero = true;
        for(char c : input) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            nuevaPieza.cantidad = stoi(input); // Convertir el n�mero a entero
            cantidadValida = true;
        } else {
            cout << "Cantidad inv�lida. Por favor, ingrese un n�mero entero v�lido." << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        }
    }
    cout << "Ingrese el nombre de la empresa proveedora: ";
    cin.ignore();
    getline(cin, nuevaPieza.proveedor);

    // Validar que el nombre de la empresa proveedora no est� vac�o
    while(nuevaPieza.proveedor.empty()) {
        cout << "El nombre de la empresa proveedora no puede estar vac�o. Por favor, ingrese un nombre v�lido." << endl;
        cout << "Ingrese el nombre de la empresa proveedora: ";
        getline(cin, nuevaPieza.proveedor);
    }
    cout << "Ingrese la factura de la empresa proveedora: ";
    cin.ignore();
    getline(cin, nuevaPieza.factura);

    // Validar que la factura de la empresa proveedora no est� vac�a
    while(nuevaPieza.factura.empty()) {
        cout << "El campo de la factura no puede estar vac�o. Por favor, ingrese un valor v�lido." << endl;
        cout << "Ingrese la factura de la empresa proveedora: ";
        getline(cin, nuevaPieza.factura);
    }
    // Validaci�n para la c�dula
    bool cedulaValida = false;
    while (!cedulaValida) {
        cout << "Ingrese el n�mero de c�dula de quien ingresa las piezas al inventario (9 d�gitos): ";
        cin >> nuevaPieza.cedula;

        if (nuevaPieza.cedula.size() == 9) {
            bool esNumero = true;
            for (char c : nuevaPieza.cedula) {
                if (!isdigit(c)) {
                    esNumero = false;
                    break;
                }
            }
            if (esNumero) {
                cedulaValida = true;
            } else {
                cout << "La c�dula debe contener s�lo n�meros. Por favor, int�ntelo de nuevo." << endl;
            }
        } else {
            cout << "La c�dula debe contener 9 d�gitos. Por favor, int�ntelo de nuevo." << endl;
        }
    }

    inventario.push_back(nuevaPieza);

    ofstream archivo("INVENTARIO.TXT", ios::app);
    archivo << nuevaPieza.codigo << "," << nuevaPieza.nombre << "," << nuevaPieza.costo << "," << nuevaPieza.cantidad << "," << nuevaPieza.proveedor << "," << nuevaPieza.factura << "," << nuevaPieza.cedula << "\n";
    archivo.close();
}

void consultarPiezaInventario(vector<Pieza>& inventario) {
    string codigo;
    cout << "Ingrese el c�digo de la pieza a consultar: ";
    cin >> codigo;

    for (auto& pieza : inventario) {
        if (pieza.codigo == codigo) {
            cout << "Informaci�n de la pieza:" << endl;
            cout << "C�digo: " << pieza.codigo << endl;
            cout << "Nombre: " << pieza.nombre << endl;
            cout << "Costo: " << pieza.costo << endl;
            cout << "Cantidad: " << pieza.cantidad << endl;
            cout << "Proveedor: " << pieza.proveedor << endl;
            cout << "Factura: " << pieza.factura << endl;
            cout << "C�dula: " << pieza.cedula << endl;
            return;
        }
    }

    cout << "Pieza no encontrada." << endl;
}

void modificarPiezaInventario(vector<Pieza>& inventario) {
    string codigo;
    cout << "Ingrese el c�digo de la pieza a modificar: ";
    cin >> codigo;

    for (auto& pieza : inventario) {
        if (pieza.codigo == codigo) {
            float nuevoCosto;
            float nuevaCantidad;
            bool cantidadValida = false;

            cout << "Ingrese el nuevo costo de la pieza: ";
            while (!(cin >> nuevoCosto)) {
                cout << "Costo inv�lido. Por favor, ingrese un n�mero v�lido." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            pieza.costo = nuevoCosto;

            while (!cantidadValida) {
                cout << "Ingrese la nueva cantidad de piezas: ";
                if (cin >> nuevaCantidad && nuevaCantidad == static_cast<int>(nuevaCantidad)) {
                    pieza.cantidad = nuevaCantidad;
                    cantidadValida = true;
                } else {
                    cout << "Cantidad inv�lida. Por favor, ingrese un n�mero entero." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            ofstream archivo("INVENTARIO.TXT");
            for (const auto& p : inventario) {
                archivo << p.codigo << "," << p.nombre << "," << p.costo << "," << p.cantidad << "," << p.proveedor << "," << p.factura << "," << p.cedula << "\n";
            }
            archivo.close();

            cout << "Pieza modificada correctamente." << endl;
            return;
        }
    }

    cout << "Pieza no encontrada." << endl;
}

void eliminarPiezaInventario(vector<Pieza>& inventario) {
    string codigo;
    cout << "Ingrese el c�digo de la pieza a eliminar: ";
    cin >> codigo;

    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if (it->codigo == codigo) {
            cout << "Informaci�n de la pieza a eliminar:" << endl;
            cout << "C�digo: " << it->codigo << endl;
            cout << "Nombre: " << it->nombre << endl;
            cout << "Costo: " << it->costo << endl;
            cout << "Cantidad: " << it->cantidad << endl;
            cout << "Proveedor: " << it->proveedor << endl;
            cout << "Factura: " << it->factura << endl;
            cout << "C�dula: " << it->cedula << endl;

            char opcion;
            cout << "�Est� seguro de eliminar esta pieza? (S/N): ";
            cin >> opcion;
            if (opcion == 'S' || opcion == 's') {
                inventario.erase(it);

                ofstream archivo("INVENTARIO.TXT");
                for (auto& p : inventario) {
                    archivo << p.codigo << "," << p.nombre << "," << p.costo << "," << p.cantidad << "," << p.proveedor << "," << p.factura << "," << p.cedula << "\n";
                }
                archivo.close();

                cout << "Pieza eliminada correctamente." << endl;
            } else {
                cout << "Operaci�n cancelada." << endl;
            }

            return;
        }
    }

    cout << "Pieza no encontrada." << endl;
}

void generarReporteInventario(vector<Pieza>& inventario) {
    cout << "REPORTE DE INVENTARIO" << endl;
    // Alineaci�n de las columnas
    cout << setw(14) << left << "CODIGO PIEZA" << "|";
    cout << setw(19) << left << "NOMBRE PIEZA" << "|";
    cout << setw(7) << left << "COSTO" << "|";
    cout << setw(9) << left << "CANTIDAD" << "|";
    cout << setw(19) << left << "PROVEEDOR" << "|";
    cout << setw(9) << left << "FACTURA" << "|";
    cout << "CEDULA EMPLEADO" << endl;

    cout << "---------------------------------------------------------------------------------------------------" << endl;

    for (auto& pieza : inventario) {
        cout << setw(14) << left << pieza.codigo << "|";
        cout << setw(19) << left << pieza.nombre << "|";
        cout << setw(7) << left << pieza.costo << "|";
        cout << setw(9) << left << pieza.cantidad << "|";
        cout << setw(19) << left << pieza.proveedor << "|";
        cout << setw(9) << left << pieza.factura << "|";
        cout << pieza.cedula << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------" << endl;

    char opcion;
    cout << "�Desea volver al men� principal? (S/N): ";
    cin >> opcion;
}

    string obtenerProximoCodigoPedido(const vector<Pedido>& pedidos) {
        int ultimoNumero = 0;
        for (const Pedido& p : pedidos) {
            if (p.codigo.find("P") == 0) {
                int numero = stoi(p.codigo.substr(1));
                ultimoNumero = max(ultimoNumero, numero);
            }
        }
        int nuevoNumero = ultimoNumero + 1;
        string nuevoCodigo = "P" + string(8 - to_string(nuevoNumero).length(), '0') + to_string(nuevoNumero);

        return nuevoCodigo;
    }


void ingresarPedido(vector<Pedido>& pedidos) {
    Pedido nuevoPedido;
    nuevoPedido.codigo = obtenerProximoCodigoPedido(pedidos); // Obtener el pr�ximo c�digo de pedido
    // Leer el c�digo de la pieza
    cout << "Ingrese el c�digo de la pieza: ";
    cin >> nuevoPedido.codigoPieza;
    // Leer la cantidad de piezas y validar que sea un n�mero entero
    bool cantidadValida = false;
    while (!cantidadValida) {
        cout << "Ingrese la cantidad de piezas: ";
        string input;
        cin >> input;

        // Verificar si el input es un n�mero entero
        bool esNumero = true;
        for(char c : input) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            nuevoPedido.cantidad = stoi(input); // Convertir el n�mero a entero
            cantidadValida = true;
        } else {
            cout << "Cantidad inv�lida. Por favor, ingrese un n�mero entero v�lido." << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        }
    }
    // Validaci�n para la c�dula
    bool cedulaValida = false;
    while (!cedulaValida) {
        cout << "Ingrese el n�mero de identificaci�n del empleado (9 d�gitos): ";
        string cedulaEmpleado;
        cin >> cedulaEmpleado;

        if (cedulaEmpleado.size() == 9) {
            bool esNumero = true;
            for (char c : cedulaEmpleado) {
                if (!isdigit(c)) {
                    esNumero = false;
                    break;
                }
            }
            if (esNumero) {
                nuevoPedido.cedulaEmpleado = cedulaEmpleado;
                cedulaValida = true;
            } else {
                cout << "La c�dula debe contener s�lo n�meros. Por favor, int�ntelo de nuevo." << endl;
            }
        } else {
            cout << "La c�dula debe contener 9 d�gitos. Por favor, int�ntelo de nuevo." << endl;
        }
    }
    // Obtener la fecha actual en formato DD/MM/YYYY
    time_t now = time(0);
    tm* ltm = localtime(&now);
    ostringstream oss;
    oss << setfill('0') << setw(2) << ltm->tm_mday << "/" << setw(2) << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900;
    nuevoPedido.fecha = oss.str();
    nuevoPedido.estado = "En proceso";

    pedidos.push_back(nuevoPedido);

    ofstream archivo("PEDIDOS.TXT", ios::app);
    archivo << nuevoPedido.codigo << "," << nuevoPedido.codigoPieza << "," << nuevoPedido.cantidad << "," << nuevoPedido.cedulaEmpleado << "," << nuevoPedido.fecha << "," << nuevoPedido.estado << "\n";
    archivo.close();
}

void consultarPedido(vector<Pedido>& pedidos) {
    string codigo;
    cout << "Ingrese el c�digo de pedido a consultar: ";
    cin >> codigo;

    for (auto& pedido : pedidos) {
        if (pedido.codigo == codigo) {
            cout << "Informaci�n del pedido:" << endl;
            cout << "C�digo de pedido: " << pedido.codigo << endl;
            cout << "C�digo de pieza: " << pedido.codigoPieza << endl;
            cout << "Cantidad: " << pedido.cantidad << endl;
            cout << "N�mero de identificaci�n del empleado: " << pedido.cedulaEmpleado << endl;
            cout << "Fecha de solicitud: " << pedido.fecha << endl;
            cout << "Estado: " << pedido.estado << endl;
            return;
        }
    }

    cout << "Pedido no encontrado." << endl;
}

void cancelarPedido(vector<Pedido>& pedidos) {
    string codigo;
    cout << "Ingrese el c�digo de pedido a cancelar: ";
    cin >> codigo;

    for (auto& pedido : pedidos) {
        if (pedido.codigo == codigo) {
            pedido.estado = "Cancelado";

            ofstream archivo("PEDIDOS.TXT");
            for (auto& p : pedidos) {
                archivo << p.codigo << "," << p.codigoPieza << "," << p.cantidad << "," << p.cedulaEmpleado << "," << p.fecha << "," << p.estado << "\n";
            }
            archivo.close();

            cout << "Pedido cancelado correctamente." << endl;
            return;
        }
    }

    cout << "Pedido no encontrado." << endl;
}

void registrarEntregaPedido(vector<Pedido>& pedidos) {
    string codigo;
    cout << "Ingrese el c�digo de pedido a marcar como entregado: ";
    cin >> codigo;

    for (auto& pedido : pedidos) {
        if (pedido.codigo == codigo) {
            pedido.estado = "Entregado";

            ofstream archivo("PEDIDOS.TXT");
            for (auto& p : pedidos) {
                archivo << p.codigo << "," << p.codigoPieza << "," << p.cantidad << "," << p.cedulaEmpleado << "," << p.fecha << "," << p.estado << "\n";
            }
            archivo.close();

            cout << "Pedido marcado como entregado correctamente." << endl;
            return;
        }
    }

    cout << "Pedido no encontrado." << endl;
}

void generarReportePedidos(vector<Pedido>& pedidos) {
    cout << "REPORTE DE PEDIDOS" << endl;

    // Alineaci�n de las columnas
    cout << setw(14) << left << "CODIGO PEDIDO" << "|";
    cout << setw(15) << left << "CODIGO PIEZA" << "|";
    cout << setw(9) << left << "CANTIDAD" << "|";
    cout << setw(19) << left << "CEDULA SOLICITANTE" << "|";
    cout << setw(15) << left << "FECHA" << "|";
    cout << setw(10) << left << "ESTADO" << endl;

    cout << "-----------------------------------------------------------------------------------" << endl;

    for (auto& pedido : pedidos) {
        cout << setw(14) << left << pedido.codigo << "|";
        cout << setw(15) << left << pedido.codigoPieza << "|";
        cout << setw(9) << left << pedido.cantidad << "|";
        cout << setw(19) << left << pedido.cedulaEmpleado << "|";
        cout << setw(15) << left << pedido.fecha << "|";
        cout << setw(10) << left << pedido.estado << endl;
    }

    cout << "-----------------------------------------------------------------------------------" << endl;

    char opcion;
    cout << "�Desea volver al men� principal? (S/N): ";
    cin >> opcion;
}


int main() {
    vector<Pieza> inventario;
    vector<Pedido> pedidos;

    // Cargar inventario desde archivo
    ifstream archivoInventario("INVENTARIO.TXT");
    if (archivoInventario.is_open()) {
        string linea;
        while (getline(archivoInventario, linea)) {
            Pieza pieza;
            size_t posicion = 0;
            string token;
            int contador = 0;

            while ((posicion = linea.find(",")) != string::npos) {
                token = linea.substr(0, posicion);

                switch (contador) {
                    case 0:
                        pieza.codigo = token;
                        break;
                    case 1:
                        pieza.nombre = token;
                        break;
                    case 2:
                        pieza.costo = stof(token);
                        break;
                    case 3:
                        pieza.cantidad = stoi(token);
                        break;
                    case 4:
                        pieza.proveedor = token;
                        break;
                    case 5:
                        pieza.factura = token;
                        break;
                    default:
                        break;
                }

                linea.erase(0, posicion + 1);
                contador++;
            }
            if (!linea.empty()) {
                pieza.cedula = linea; // Asignar lo que queda en la l�nea a estado
            }

            inventario.push_back(pieza);
        }

        archivoInventario.close();
    }

    ifstream archivoPedido("PEDIDOS.TXT");
    if (archivoPedido.is_open()) {
        string linea;
        while (getline(archivoPedido, linea)) {
            Pedido pedido;
            size_t posicion = 0;
            string token;
            int contador = 0;

            while ((posicion = linea.find(",")) != string::npos) {
                token = linea.substr(0, posicion);

                switch (contador) {
                    case 0:
                        pedido.codigo = token;
                        break;
                    case 1:
                        pedido.codigoPieza = token;
                        break;
                    case 2:
                        pedido.cantidad = stoi(token);
                        break;
                    case 3:
                        pedido.cedulaEmpleado = token;
                        break;
                    case 4:
                        pedido.fecha = token;
                        break;
                    default:
                        break;
                }

                linea.erase(0, posicion + 1);
                contador++;
            }

            if (!linea.empty()) {
                pedido.estado = linea; // Asignar lo que queda en la l�nea a estado
            }

            pedidos.push_back(pedido);
        }

        archivoPedido.close();
    }


    string opcion;
    do {
        cout << "Men� de opciones:" << endl;
        cout << "1. Inventario" << endl;
        cout << "2. Pedido" << endl;
        cout << "3. Reporte de Inventario" << endl;
        cout << "4. Reporte de Pedidos" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese la opci�n que desee: ";
        cin >> opcion;

        if (opcion == "5") {
            break;
        }

        int numOpcion;
        try {
            numOpcion = stoi(opcion);
        } catch(exception e) {
            cout << "Opci�n inv�lida." << endl;
            continue;
        }

        switch (numOpcion) {
            case 1:
                // Men� de inventario
                cout << "Men� de Inventario:" << endl;
                cout << "a. Ingresar pieza al inventario" << endl;
                cout << "b. Consultar pieza del inventario" << endl;
                cout << "c. Modificar pieza del inventario" << endl;
                cout << "d. Eliminar pieza del inventario" << endl;
                char subopcion;
                cout << "Ingrese la opci�n que desee: ";
                cin >> subopcion;
                switch (subopcion) {
                    case 'a':
                        agregarPiezaInventario(inventario);
                        break;
                    case 'b':
                        consultarPiezaInventario(inventario);
                        break;
                    case 'c':
                        modificarPiezaInventario(inventario);
                        break;
                    case 'd':
                        eliminarPiezaInventario(inventario);
                        break;
                    default:
                        cout << "Opci�n inv�lida." << endl;
                        break;
                }
                break;
            case 2:
                // Men� de Pedido
            cout << "Men� de Pedido:" << endl;
            cout << "a. Ingreso de pedido" << endl;
            cout << "b. Consulta de Pedido" << endl;
            cout << "c. Cancelar Pedido" << endl;
            cout << "d. Registrar entrega de pedido" << endl;
            char subopcionPedido;
            cout << "Ingrese la opci�n que desee: ";
            cin >> subopcionPedido;
            switch (subopcionPedido) {
                case 'a':
                    ingresarPedido(pedidos);
                    break;
                case 'b':
                    consultarPedido(pedidos);
                    break;
                case 'c':
                    cancelarPedido(pedidos);
                    break;
                case 'd':
                    registrarEntregaPedido(pedidos);
                    break;
                default:
                    cout << "Opci�n inv�lida." << endl;
                    break;
            }
            break;
            case 3:
                generarReporteInventario(inventario);
                break;
            case 4:
                generarReportePedidos(pedidos);
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opci�n inv�lida." << endl;
                break;
        }
    } while (opcion != "5");

    return 0;
}
