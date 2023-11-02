#ifndef USERREPOSITORY_H_INCLUDED
#define USERREPOSITORY_H_INCLUDED

Usuario buscarUsuario(const char *nomeDeUsuario);

bool inserirUsuario(const char* nomeDeUsuario, const char* senha);

#endif // USERREPOSITORY_H_INCLUDED
