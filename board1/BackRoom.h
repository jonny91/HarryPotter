void init()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
}

void delay_ms(int count)  // /* X1ms */	 ��ʱ1ms����
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}