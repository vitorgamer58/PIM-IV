#ifndef FILEHELPER_H_INCLUDED
#define FILEHELPER_H_INCLUDED

FILE* criarArquivo(const char* nomeDoArquivo);
FILE* abrirOuCriarArquivo(const char* nomeDoArquivo);
FILE* abrirArquivoParaGravacao(const char* nomeDoArquivo);
void gravarStringNoArquivo(const char* nomeDoArquivo, const char* stringParaGravar);

#endif // FILEHELPER_H_INCLUDED
