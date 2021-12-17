#include "Public/Public_Var.h"

Public_Var* Public_Var::Var = new Public_Var();
Public_Var::Public_Var()
{
//    this->Init();
}

Public_Var::~Public_Var()
{

}

Public_Var* Public_Var::Get()
{
    return Var;
}
