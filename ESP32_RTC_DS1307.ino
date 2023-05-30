#include "RTCDS1307.h"

/*
 * Modificacion del ejemplo que esta en la libreria https://github.com/offcircuit/RTCDS1307
 * por JToobe
 * Alimentacion: 5v
 * SCL => D22
 * SDA => D21
 */

RTCDS1307 rtc(0x68); // Crear una instancia del objeto RTCDS1307 con la dirección I2C 0x68

uint8_t year, month, weekday, day, hour, minute, second; // Variables para almacenar la fecha y hora
bool period = 0; // Variable para indicar el periodo AM/PM

String m[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}; // Matriz de nombres de los meses
String w[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"}; // Matriz de nombres de los días de la semana

void setup()
{
  Serial.begin(115200); // Iniciar la comunicación serial
  rtc.begin(); // Inicializar el módulo RTC

  // rtc.setDate(23, 5, 30); // Establecer una fecha específica en el RTC
  // rtc.setTime(14, 40, 50); // Establecer una hora específica en el RTC
}

void loop()
{
  rtc.getDate(year, month, day, weekday); // Obtener la fecha del RTC
  rtc.getTime(hour, minute, second, period); // Obtener la hora del RTC

  if (!(second % 3)) // Cambiar el modo AM/PM cada 3 segundos
    rtc.setMode(1 - rtc.getMode());

  rtc.getTime(hour, minute, second, period); // Obtener la hora actualizada del RTC

  Serial.print(w[weekday - 1]); // Mostrar el nombre del día de la semana
  Serial.print("  ");
  Serial.print(day, DEC); // Mostrar el día del mes
  Serial.print("/");
  Serial.print(m[month - 1]); // Mostrar el nombre del mes
  Serial.print("/");
  Serial.print(year + 2000, DEC); // Mostrar el año
  Serial.print("  ");
  Serial.print(hour, DEC); // Mostrar la hora
  Serial.print(":");
  Serial.print(minute, DEC); // Mostrar los minutos
  Serial.print(":");
  Serial.print(second, DEC); // Mostrar los segundos
  Serial.print(rtc.getMode() ? (period ? " PM" : " AM") : ""); // Mostrar el periodo AM/PM
  Serial.println();
  
  delay(1000); // Esperar 1 segundo
}
