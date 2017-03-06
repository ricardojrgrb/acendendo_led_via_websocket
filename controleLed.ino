// Biblioteca necessária para utilização do Módulo Ethernet ENC28J60;
#include <UIPEthernet.h>
#include <SPI.h>

// Definição dos Pinos utilizados para os Leds;
#define gpio_11 11
#define gpio_12 12

// Instanciamento do serviço de rede com atribuição de um nome 
// para o servidor(server) e da porta(80) utilizada;
EthernetServer server = EthernetServer(80);

void setup()
{
	// Deifinindo os pinos como pinos de saída;
	pinMode(gpio_11, OUTPUT);
	pinMode(gpio_12, OUTPUT);

	Serial.begin(9600);

	//As funções abaixo são nativas da biblioteca UIPEthernet.h

	// Endereço MAC para o módulo de rede(Não precisa ser alterado 
	//caso tenha apenas este módulo em sua rede);
	uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
	// Endereço IP para o Arduino;
  	IPAddress myIP(10,1,52,46);
  	// Função que envia os endereços MAC e IP para o módulo de rede;
  	Ethernet.begin(mac,myIP);
  	// Função que inicia o módulo de rede de acordo com as atribuições anteriores;  
  	server.begin();

}

void loop()
{
	// Declaração da variável client que receberá as requisições de server.available();
	EthernetClient client = server.available();

	// Estrutura de seleção que receberá as requisições do socket criado em arduino.php; 
	if(client)
    { 
    	// client.read() - Função nativa da bíblioteca UIPEthernet.h que recebrá o valor do scoket;
	    client.println("<html>");
	    client.println("<body>");
	    client.println("<h1>TESTE ETHER_28J60</h1>");
	    client.println("</body>");
	    client.println("</html>");
	    
		switch (client.read())
		{	
			// '1' - Valor recebido do socket que acionará a função digitalWrite(gpio_11, HIGH);
		    case '1':
		      digitalWrite(gpio_11, HIGH);
		      Serial.print("Acende LED 01");
		      break;
		    case '2':
		      digitalWrite(gpio_12, HIGH);
		      Serial.print("Acende LED 02");
		      break;
		    case '3':
		      digitalWrite(gpio_11, LOW);
		      Serial.print("Apaga LED 01");
		      break;
		    case '4':
		      digitalWrite(gpio_12, LOW);
		      Serial.print("Apaga LED 02");
		      break;    
		    default:
		      delay(1);
		}
	}
	// client.stop() - Função que para o serviço de rede até que chegue 
	//uma nova requisição via socket;
    client.stop();
}