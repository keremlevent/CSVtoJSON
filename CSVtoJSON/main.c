#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	
	
	// [Terminal için argüman belirleme]

	
	//Hangi dosyalar arasinda convert yapacagini terminalden belirle.
	char *argOku=argv[1];
	char *argYaz=argv[2];
	// Header on off
	char *argHeader=argv[3];
	
	if(argc==4){
	printf("[CSVtoJSON] basarili.");
	}
	
	
	
	//Dosya islemleri acilisi
	
	FILE *pr;
	pr=fopen(argOku,"r");
		if(pr==NULL){
		printf("[R]Dosya acilmadi.");
		exit(1);
	}
	
	FILE *pw;
	pw=fopen(argYaz,"w");
		if(pw==NULL){
		printf("[W]Dosya acilmadi.");
		exit(1);
	}
	

	char ilkSatir[100];
	char satirChar;
    int i;
    int sutunSayisi=1;
    
		//[Sütun sayisinin belirlenmesi]
		
		fscanf(pr,"%s",ilkSatir);
	
	for(i=0;i<100;i++){
		
		  satirChar=ilkSatir[i];
		  
		  if(satirChar == ','){
		  sutunSayisi++;
		}
    }
      	
      
	
	// [CSV TO JSON]
	rewind(pr);
	char karakter;
	char tirnak='"';
	char ikiNokta=':';
	char virgul=',';
	char solsParantez='}';
	char sagsParantez='{';
	
	char header[10][100];

	fputs("[\n",pw);
	while(!feof(pr)){
	fputs("{\n",pw);
	
		for(i=0;i<sutunSayisi;i++){
			fprintf(pw,"%c%s%d%c%c",tirnak,"header",i,tirnak,ikiNokta);
			fputc(tirnak,pw);
			do{
				
				karakter=getc(pr);
				if(karakter!=','&& karakter!='\n'){
					fputc(karakter,pw);
				}
				else{
					if(karakter==','){

 //\n ile alt satira atlarken fputs ve fputc komutu sorun cikartiyor (son karaktere X yazip asagi satira iniyor).
					fprintf(pw,"%c%c\n",tirnak,virgul);
						break;
					}
					if(karakter=='\n'){
						fprintf(pw,"%c\n",tirnak);
						fprintf(pw,"},\n",solsParantez,virgul);  //Birden fazla karakter yazarken fprintf kullanmak mantiklidir char ve string komutu sorun cikartabiliyor.
						break;
					}
				}
			}
			
			while(karakter!=EOF);
			
		}
	}
	fputs("\n]",pw);
	
	fclose(pr);
	fclose(pw);

	return 0;
}
