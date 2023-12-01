# include <SoftwareSerial.h>

# define rx 2
# define tx 3

SoftwareSerial myserial(rx, tx);

String inputstring = "";
String sensorstring = "";
boolean input_string_complete = false;
boolean sensor_string_complete = false;

void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  inputstring.reserve(10);
  sensorstring.reserve(30);
}

void serialEvent() {
  inputstring = Serial.readStringUntil(13);
  input_string_complete = true;
}

void print_color_name(int red, int green, int blue) {
  // Comparación de valores RGB para determinar el color
  if (red < 20 && green < 20 && blue < 20) {
    Serial.println("Color: Negro");
  } else if (red > 100 && green < 35 && blue < 35) {
    Serial.println("Color: Rojo");
  } else if (red > 120 && green < 60 && blue < 55) {
    Serial.println("Color: Naranja");
  } else if (red > 300 && green > 250 && blue < 150) {
    Serial.println("Color: Amarillo");
  } else if (red > 80 && green > 130 && blue < 85) {
    Serial.println("Color: Verde");
  } else if (red < 35 && green > 40 && blue > 80) {
    Serial.println("Color: Azul");
  } else if (red > 135 && green < 65 && blue > 50) {
    Serial.println("Color: Púrpura");
  }else if (red > 60 && green > 40 && blue < 65){
    Serial.println("Color: Cafe");
  }else if (red > 150 && green > 150 && blue > 150) {
    Serial.println("Color: Blanco");
  } else if (red < 100 && green < 100 && blue < 200) {
    Serial.println("Color: Gris");
  } else {
    Serial.println("Color: Desconocido");
  }
}

void loop() {
  if (input_string_complete == true) {
    myserial.print(inputstring);
    myserial.print('\r');
    inputstring = "";
    input_string_complete = false;
  }

  if (myserial.available() > 0) {
    char inchar = (char)myserial.read();
    sensorstring += inchar;
    if (inchar == '\r') {
      sensor_string_complete = true;
    }
  }

  if (sensor_string_complete == true) {
    if (isdigit(sensorstring[0]) == false) {
      Serial.println(sensorstring);
    } else {
      print_RGB_data();  // Aquí deberías llamar a la función print_color_name en lugar de print_RGB_data
    }
    sensorstring = "";
    sensor_string_complete = false;
  }
}

void print_RGB_data(void) {
  char sensorstring_array[30];
  char *red;
  char *grn;
  char *blu;
  int int_red;
  int int_grn;
  int int_blu;

  sensorstring.toCharArray(sensorstring_array, 30);
  red = strtok(sensorstring_array, ",");
  grn = strtok(NULL, ",");
  blu = strtok(NULL, ",");

  Serial.print("RED:");
  Serial.println(red);

  Serial.print("GREEN:");
  Serial.println(grn);

  Serial.print("BLUE:");
  Serial.println(blu);

  int_red = atoi(red);
  int_grn = atoi(grn);
  int_blu = atoi(blu);

  print_color_name(int_red, int_grn, int_blu);
}