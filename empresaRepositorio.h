#ifndef EMPRESAREPOSITORIO_H_INCLUDED
#define EMPRESAREPOSITORIO_H_INCLUDED

#include "listas/listas.h"

bool inserirEmpresa(Empresa empresa);
Empresa buscarEmpresa(const char *cnpj);
ListaDeEmpresas* buscarTodasEmpresas();

#endif // EMPRESAREPOSITORIO_H_INCLUDED
