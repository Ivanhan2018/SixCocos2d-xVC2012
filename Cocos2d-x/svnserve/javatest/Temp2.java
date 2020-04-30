public class Temp2{
 public static void main (String args[]) {
//int []aBGR = {0x56, 0x78, 0x9A, 0xBC};   // 是用16进制保存的4种颜色值
//int []aBGR = {0,42,227,230};
//int []aBGR = {0,255,195,198};
int []aBGR = {0,255,0,0};
int color_val = aBGR[3];   
color_val = color_val | (aBGR[2] << 8);  // 为了压缩，需要放置到color_val值的第二个字节位置上：将aRGB[2] 左移到第二个byte，同时与color_val进行或操作，下面同理
color_val = color_val | (aBGR[1] << 16);  
color_val = color_val | (aBGR[0] << 24);                
//ff0000=16711680=(0,0,255)
//ffc3c6=16761798=(198,195,255) 

//2ae3e6=2810854
//RGB(230,227,42),COLORREF rgb=2810854,BYTE r=230,g=227,b=42;r=2810854%256;g=(2810854/256)%256;b=2810854/256/256;Mod=%

//操作完的结果是56789abc=1450744508
System.out.println(Integer.toHexString(color_val)); 
System.out.println(color_val);
 }
}