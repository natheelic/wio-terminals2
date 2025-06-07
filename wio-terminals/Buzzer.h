#ifndef BUZZER_H
#define BUZZER_H

void buzzer_init();
void beep_success(); // ตั้งชื่อให้เป็นกลางมากขึ้น
void beep_fail();
void beep_short(int count = 1); // ฟังก์ชันเสริมสำหรับเสียงสั้นๆ

#endif