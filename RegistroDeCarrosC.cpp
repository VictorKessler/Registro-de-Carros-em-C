#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados_carro{
	char dono[40];
	char placa[10];
	char modelo[20];
	float preco;
};

void registra_carro (FILE *arquivo, dados_carro carro);
void excluir_carro (FILE *arquivo, dados_carro carro);
void edita_carro (FILE *arquivo, dados_carro carro);
void busca_carro (FILE *arquivo, dados_carro carro);
void lista_carro (FILE *arquivo, dados_carro carro);

int main (void){
	FILE *arquivo;
	int opc;
	dados_carro carro;

	do {
		printf ("\n\n###---------------Digite a opcao desejada---------------###:\n\n");
		printf ("1- Registrar um novo carro\n2- Apagar um carro\n3- Editar dados de um carro\n4- Consultar carro pela placa\n5- Ver a lista de carros completa\n6- Sair do programa\n\n");
		scanf ("%d", &opc);
		fflush (stdin);
		
		switch (opc){
			
			case 1:
				system ("cls");
				
				registra_carro (arquivo, carro);	
				
				break;
			
			case 2:
				system ("cls");
				
				excluir_carro (arquivo, carro);
				
				break;
				
			case 3:
				system ("cls");
				
				edita_carro (arquivo, carro);
				
				break;
				
			case 4:
				system ("cls");
				
				busca_carro (arquivo, carro);
				
				break;
				
			case 5:
				system ("cls");
				
				lista_carro (arquivo, carro);
				
				break;
			
			case 6:
				system ("cls");
				
				opc = 6;
			
				break;
				
			default:
				printf ("Escolha uma opcao valida");
				
				break;				
		}
		
	} while (opc != 6);	
}

void registra_carro (FILE *arquivo, dados_carro carro){		
	arquivo = fopen ("arquivomanipulado.bin", "a+b");
		
	if (arquivo == NULL){
		puts ("nao foi possivel abrir o arquivo");
	}else{	
		printf("Qual o nome do dono?  ");
		gets (carro.dono);
		fflush(stdin);
		
		printf("Qual a placa do carro?  ");
		gets(carro.placa);
		fflush(stdin);
		
		printf("Qual o modelo do carro?  ");
		gets(carro.modelo);
		fflush(stdin);
		
		printf("Qual o preco do carro?  ");
		scanf("%f", &carro.preco);
		fflush(stdin);
				
		fwrite(&carro, sizeof (carro), 1, arquivo);
	}
	
	fclose (arquivo);
}

void excluir_carro (FILE *arquivo, dados_carro carro){
	char str_auxiliar[7];
	FILE *temp;
	int flag;
	
	arquivo = fopen ("arquivomanipulado.bin", "r+b");
	temp = fopen ("temp.bin", "w+b");
		
	if (arquivo == NULL || temp == NULL){
		puts ("nao foi possivel abrir o arquivo");
	}else{
		printf ("Qual a placa do carro que deseja excluir?  ");
		gets (str_auxiliar);
		fflush (stdin);
		
		while (fread(&carro, sizeof (carro), 1, arquivo) == 1){
			if (strcmp (carro.placa, str_auxiliar) != 0){	
				fwrite(&carro, sizeof (carro), 1, temp);
			} else {
				flag = 1;
			}
		}
			
		if (flag = 1){
			fclose (temp);
			fclose (arquivo);
			remove ("arquivomanipulado.bin");
			rename ("temp.bin", "arquivomanipulado.bin");	
			printf ("\nCarro excluido com sucesso!");
		}
	}
}

void edita_carro (FILE *arquivo, dados_carro carro){
	char str_auxiliar[7];
	int posicao = 0, sucesso = 0, resposta;
	
	arquivo = fopen ("arquivomanipulado.bin", "rb+");
	
	if (arquivo == NULL){
		puts ("nao foi possivel abrir o arquivo");
	}else{
		
		printf("Qual a placa do carro que deseja encontrar?  ");
		gets(str_auxiliar);
		fflush(stdin);
		
		fseek(arquivo, posicao, SEEK_SET);
		
		do {
			if (fread(&carro, sizeof (carro), 1, arquivo) == 0){
				break;
			}
			
			if (strcmp (carro.placa, str_auxiliar) == 0){
				
				printf ("\nO registro atual:");
				printf ("\n\nNome do dono: %s", carro.dono);
				printf ("\nPlaca do carro: %s", carro.placa);
				printf ("\nModelo do carro: %s", carro.modelo);
				printf ("\nPreco do carro: %.2f", carro.preco);
				
				printf ("\n\nO que deseja editar:\n\n1- Nome do dono\n2- Placa\n3- Modelo\n4- Preco\n\n");
				scanf ("%d", &resposta);
				fflush (stdin);
				
				switch (resposta){
					case 1:
						printf ("Digite o nome do novo dono:  ");
						gets (carro.dono);
						fflush (stdin);
						
						break;
						
					case 2:
						printf ("Digite a nova placa:  ");
						gets (carro.placa);
						fflush (stdin);
						
						break;
						
					case 3:
						printf ("Digite o novo modelo:  ");
						gets (carro.modelo);
						fflush (stdin);
						
						break;
						
					case 4:
						printf ("Digite o novo preco:  ");
						scanf("%f", &carro.preco);
						fflush (stdin);
						
						break;
						
					default:
						printf ("Escolha uma opcao valida");
				
						break;
				}
				
				fseek (arquivo, posicao, SEEK_SET);
				
				fwrite(&carro, sizeof(carro), 1, arquivo);
				
				sucesso = 1;
								
				break;	
			}
			
			posicao = posicao + sizeof (carro);
			
		}while(1);
		
		if (!sucesso){
			printf ("nao foi possivel editar :(");
		}
			
		fclose (arquivo);
	}
}

void busca_carro (FILE *arquivo, dados_carro carro){
	char str_auxiliar[7];
	int posicao = 0, sucesso = 0;
	
	arquivo = fopen ("arquivomanipulado.bin", "r+b");
	
	if (arquivo == NULL){
		puts ("nao foi possivel abrir o arquivo");
	}else{
		
		printf("Qual a placa do carro que deseja encontrar?  ");
		gets(str_auxiliar);
		fflush(stdin);
		
		fseek(arquivo, posicao, SEEK_SET);
		
		do {
			if (fread(&carro, sizeof (carro), 1, arquivo) == 0){
				break;
			}
			
			if (strcmp (carro.placa, str_auxiliar) == 0){
				printf ("\nNome do dono: %s", carro.dono);
				printf ("\nPlaca do carro: %s", carro.placa);
				printf ("\nModelo do carro: %s", carro.modelo);
				printf ("\nPreco do carro: %.2f", carro.preco);
				
				fseek (arquivo, posicao, SEEK_END);
			}
		}while(1);
			
		fclose (arquivo);
	}
}

void lista_carro (FILE *arquivo, dados_carro carro){	
	arquivo = fopen ("arquivomanipulado.bin", "a+b");
	
	if (arquivo == NULL){
		puts ("nao foi possivel abrir o arquivo");
	}else{
		while (fread(&carro, sizeof (carro), 1, arquivo) == 1){
			printf ("\nNome do dono: %s", carro.dono);
			printf ("\nPlaca do carro: %s", carro.placa);
			printf ("\nModelo do carro: %s", carro.modelo);
			printf ("\nPreco do carro: %.2f", carro.preco);	
	
			printf ("\n\n");
		}
	}
	
	fclose (arquivo);
}