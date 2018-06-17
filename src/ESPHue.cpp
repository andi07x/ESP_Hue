/**************************************************************************
				= Philips Hue Library for ESP8266 =

	This library is designed to access and control Philips Hue Lights Directly.

    Written by: Richard Wardlow @ Circuits for Fun, LLC
    GNU GPL, include above text in redistribution
***************************************************************************/

#include <ESPHue.h>
#include <WiFiClient.h>

////////////////////////////////////////
// ESPHue Class Methods
////////////////////////////////////////
ESPHue::ESPHue(WiFiClient& client, const char* APIKey, const char* host, uint8_t port)
{
	_client = &client;
	_apiKey = APIKey;
	_host = host;
	_port = port;
  _restclient = RestClient(client, host);
}

void ESPHue::setAPIKey(const char* APIKey)
{
	_apiKey = APIKey;
}

void ESPHue::setHubIP(const char* host)
{
	_host = host;
}

void ESPHue::setHubPort(uint8_t port)
{
	_port = port;
}

String ESPHue::getLightInfo(byte lightNum)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return "";
  }
  String url = "/api/" + String(_apiKey) + "/lights/" + lightNum;
  _restclient.get(url);
  return _restclient.readResponse();
}

int ESPHue::getLightState(byte lightNum)
{
    int lightState = 0;
    String response = getLightInfo(lightNum);

    if (response.indexOf("\"on\":false") != -1)
    {
      lightState = 0;
    }
    if (response.indexOf("\"on\":true") != -1)
    {
      lightState = 1;
    }
    return lightState;
}

void ESPHue::setLight(byte lightNum, byte state, byte sat, byte bri, unsigned int hue)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/lights/" + lightNum + "/state";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true,";
  else
    cmd += "false,";
  cmd += " \"sat\":" + String(sat) + ", \"bri\":" + String(bri) + ", \"hue\":" + String(hue) + "}";
  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}

void ESPHue::setLight(byte lightNum, byte state, byte sat, byte bri, unsigned int hue, unsigned int trans)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/lights/" + lightNum + "/state";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true,";
  else
    cmd += "false,";
  cmd += " \"sat\":" + String(sat) + ", \"bri\":" + String(bri) + ", \"hue\":" + String(hue) + ", \"transitiontime\":" + String(trans) + "}";
  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}

void ESPHue::setLightPower(byte lightNum, byte state)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/lights/" + lightNum + "/state";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true}";
  else
    cmd += "false}";

  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}


String ESPHue::getGroupInfo(byte groupNum)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return "";
  }
  String url = "/api/" + String(_apiKey) + "/groups/" + groupNum;
  _restclient.get(url);
  return _restclient.readResponse();
}

int ESPHue::getGroupState(byte groupNum)
{
    int groupState = 0;
    String response = getGroupInfo(groupNum);

    if (response.indexOf("\"on\":false") != -1)
    {
      groupState = 0;
    }
    if (response.indexOf("\"on\":true") != -1)
    {
      groupState = 1;
    }
    return groupState;
}

void ESPHue::setGroup(byte groupNum, byte state, byte sat, byte bri, unsigned int hue)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/groups/" + groupNum + "/action";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true,";
  else
    cmd += "false,";
  cmd += " \"sat\":" + String(sat) + ", \"bri\":" + String(bri) + ", \"hue\":" + String(hue) + "}";
  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}

void ESPHue::setGroup(byte groupNum, byte state, byte sat, byte bri, unsigned int hue, unsigned int trans)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/groups/" + groupNum + "/action";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true,";
  else
    cmd += "false,";
  cmd += " \"sat\":" + String(sat) + ", \"bri\":" + String(bri) + ", \"hue\":" + String(hue) + ", \"transitiontime\":" + String(trans) + "}";
  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}

void ESPHue::setGroupPower(byte groupNum, byte state)
{
  if (!_client->connect(_host, _port)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/" + String(_apiKey) + "/groups/" + groupNum + "/action";
  String cmd = "{\"on\":";
  if (state == 1)
    cmd += "true}";
  else
    cmd += "false}";

  _restclient.put(url, cmd);
  String ret = _restclient.readResponse();
}
