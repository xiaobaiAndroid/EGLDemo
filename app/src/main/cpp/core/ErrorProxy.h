/**
 *@author: baizf
 *@date: 2022/12/4
*/
//

#ifndef OPENGLDEMO_ERRORPROXY_H
#define OPENGLDEMO_ERRORPROXY_H

#include <string>

using namespace std;

class ErrorProxy{
public:
    static void checkError(string message = "");
};

#endif //OPENGLDEMO_ERRORPROXY_H
