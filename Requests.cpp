#include "Requests.h"
Requests::Requests(float req, string requesterr, string recieve)
{
    requestAmount = req;
    requester = requesterr;
    reciever = recieve;

}
Requests::Requests()
{
    requestAmount = 2.0;
    requester = "requesterr";
    reciever = "recieve";
}
Requests::~Requests(void)
{

}