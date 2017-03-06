<?php

// $sock - Variável declarada para ciração do socket;
// socket_create - Função nativa do PHP para habilitar o novo socket;
// http://php.net/manual/pt_BR/function.socket-create.php - Tutorial completo sobre a função socket_create e seus parâmetros;
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);

// socket_connect - Função que irá conectar o web socket desenvolvido em PHP com o Arduino;
// Parâmetros do socket_connect - (Nome do scoket, IP do Arduino, Porta);
socket_connect($sock,"10.1.52.46", 80);

// Estrutura de seleção que receberá as requisições da interface web(index.html) e associar com o parâmetro do $_POST['estadoLed'];
if ($_POST['estadoLed']=="lverde_ligado")
{
	// socket_write - Função nativa do PHP que enviará via socket o valor("1") para estrutura de seleção(switch (client.read()) do arduino,
	// para acionamento do LED;
    socket_write($sock, "1");
}
if ($_POST['estadoLed']=="lvermelho_ligado")
{
    socket_write($sock, "2");
}
if ($_POST['estadoLed']=="lverde_desligado")
{
    socket_write($sock, "3");
}
if ($_POST['estadoLed']=="lvermelho_desligado")
{
    socket_write($sock, "4");
}

// header - Função nativa do PHP que retorna a index.html após acionamento dos botões;
header("Location: index.html");

// socket_close - Função nativa do PHP que encerra a conexão com o socket;
socket_close($sock);
?>   