#include <gtk/gtk.h>
#include <stdio.h>
#include "sudoku.h"
static GtkWidget *buttons[9][9];
static int numbers[9][9];
static int countBut=0;
GtkWidget *myWindow;
int myindex;
gboolean eventWindow (GtkWidget *a,GdkEvent *aa,gpointer aaa){
 if(aa->key.string[0]==13){
  mainSud(numbers);
  myindex=0;
  return(TRUE);
 }else{
  return(FALSE);
 }
}
void settedNum(int num,int i,int k){
 char a[2];
 a[1]=0;
 if(num==0){
  a[0]=0;
 }else{
  a[0]=num+48;
 }
 gtk_button_set_label((GtkButton *)buttons[i][k],a);
}
gboolean eventPress (GtkWidget *a,GdkEvent *aa,gpointer aaa){
 if((aa->key.string[0]>47) && (aa->key.string[0]<58)){
  numbers[((int) aaa)/9][((int) aaa)%9]=aa->key.string[0]-48;
  settedNum(aa->key.string[0]-48,((int) aaa)/9,((int) aaa)%9);
  if(aaa<80){
   gtk_widget_grab_focus(buttons[((int) aaa+1)/9][((int) aaa+1)%9]);
  }else {
   gtk_widget_grab_focus(buttons[0][0]);
  }
  return(TRUE);
 }
 return(FALSE);
}
gint eventDelete (GtkWidget *a,GdkEvent *aa,gpointer aaa){
 return(FALSE);
}
gint eventDestroy (GtkWidget *a,GdkEvent *aa,gpointer aaa){
 gtk_main_quit();
}
void registerButton(GtkWidget *button){
 static int countBut=0;
 numbers[countBut/9][countBut%9]=0;
 int a=countBut/9;
 int b=countBut%9;
 getCoord(&a,&b,2);
 buttons[a][b]=button;
 gtk_signal_connect((GtkObject *)button,"key_press_event",GTK_SIGNAL_FUNC(eventPress),a*9+b);
 countBut++;
}
GtkWidget *makeButton(){
 GtkWidget *button;
 button=gtk_button_new();
 registerButton(button);
 return(button);
}
GtkWidget *makeBox(){
 GtkWidget *box;
 box=gtk_hbox_new(TRUE,0);
 for(int i=0;i<3;i++){
  gtk_box_pack_start((GtkBox *)box,makeButton(),TRUE,TRUE,0);
 }
 return(box);
}
GtkWidget *makeBlock(){
 GtkWidget *box;
 box=gtk_vbox_new(TRUE,0);
 for(int i=0;i<3;i++){
  gtk_box_pack_start((GtkBox *)box,makeBox(),TRUE,TRUE,0);
 }
 gtk_container_set_border_width((GtkContainer *)box,5);
 return(box);
}
GtkWidget *makeBlockBox(){
 GtkWidget *box;
 box=gtk_hbox_new(TRUE,0);
 for(int i=0;i<3;i++){
  gtk_box_pack_start((GtkBox *)box,makeBlock(),TRUE,TRUE,0);
 }
 return(box);
}
GtkWidget *makeTable(){
 GtkWidget *box;
 box=gtk_vbox_new(TRUE,0);
 for(int i=0;i<3;i++){
  gtk_box_pack_start((GtkBox *)box,makeBlockBox(),TRUE,TRUE,0);
 }
 return(box);
}
int main(int argc,char *argv[]){
 gtk_init(&argc,&argv);
 myWindow =gtk_window_new (GTK_WINDOW_TOPLEVEL);
 gtk_signal_connect(GTK_OBJECT(myWindow),"delete-event",GTK_SIGNAL_FUNC(eventDelete),NULL);
 gtk_signal_connect(GTK_OBJECT(myWindow),"destroy",GTK_SIGNAL_FUNC(eventDestroy),NULL);
 gtk_signal_connect(GTK_OBJECT(myWindow),"key_press_event",GTK_SIGNAL_FUNC(eventWindow),NULL);
 gtk_window_set_title(myWindow,"Sudoku game.");
 GtkWidget *table=makeTable();
 gtk_container_add((GtkContainer *)myWindow,table);
 gtk_window_set_default_size(myWindow,192,255);
 gtk_widget_show_all(myWindow);
 gtk_main();
}