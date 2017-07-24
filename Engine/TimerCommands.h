///////////////////////////////////////////////////////

//functions for the timer
#pragma region TimerCommands

void tm_init ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_factor = 1;
}

float tm_update ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_difference = user[0].tm_timer - user[0].tm_last;
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_result = user[0].tm_difference * user[0].tm_factor;
   return user[0].tm_result;
}
void tm_setmultiplicator ( float f_flt )
{
   user[0].tm_factor = f_flt;
}
float tm_getfactor ()
{
   float f_flt = 0;
   f_flt = user[0].tm_result;
   return f_flt;
}

#pragma endregion
/////////////////////////