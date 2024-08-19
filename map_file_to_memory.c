#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Obtém o tamanho atual do arquivo
    struct stat file_info;
    if (fstat(fd, &file_info) == -1) {
        perror("Error getting file size");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t file_size = file_info.st_size;

    // Se o arquivo for vazio, define um tamanho mínimo para o mapeamento
    if (file_size == 0) {
        file_size = 4096; // 4 KB
        if (ftruncate(fd, file_size) == -1) {
            perror("Error setting file size");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // Mapeia o arquivo na memória
    void *map = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Escreve no arquivo mapeado na memória
    const char *message = "Este é um teste de escrita em memória virtual mapeada!\n";
    size_t message_len = strlen(message);

    if (message_len > file_size) {
        // Se a mensagem for maior que o tamanho do arquivo, aumenta o mapeamento
        if (ftruncate(fd, message_len) == -1) {
            perror("Error extending file size");
            munmap(map, file_size);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Remapeia a memória com o novo tamanho
        munmap(map, file_size);
        file_size = message_len;
        map = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            perror("Error remapping file");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    memcpy(map, message, message_len);

    // Sincroniza a memória mapeada com o arquivo no disco
    if (msync(map, file_size, MS_SYNC) == -1) {
        perror("Error syncing file");
    }

    // Exibe informações sobre o uso de memória virtual
    printf("Arquivo mapeado para a memória virtual e escrito com sucesso.\n");
    printf("Endereço da memória mapeada: %p\n", map);
    printf("Tamanho da memória mapeada: %zu bytes\n", file_size);

    // Desmapeia a memória e fecha o arquivo
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping memory");
    }

    close(fd);
    return 0;
}
