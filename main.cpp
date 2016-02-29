#include <iostream>
#include "http_client.h"
#include "hudmsg_reader.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

//  std::string foo;
//  HttpClient *client = new HttpClient("time.khobho.co.jp");
//  client->get_data("/ohmi_bus/tim_dsp.asp?projCd=1&eigCd=2&teicd=3314&KaiKbn=NOW&pole=1",foo);
//  std::cout << foo;


  HudmsgReader hudmsg;
  hudmsg.get_msg();

  return 0;
}