


#include <ros.h>
#include <rospy_tutorials/Floats.h>
#include <robotic_arm_pkg/Floats_array.h>
#include <Servo.h> 

ros::NodeHandle  nh;

int a0,a4;
int cur_pos[5]={0,0,0,0,0};

Servo base,shoulder,elbow,wrist1,wrist2,claw;

float readbase=0,readshoulder=0,readelbow=0,readwrist1=0,readwrist2=0,readservo5=0;

void rotate_servo(int servo,int new_pos,int cur_pos,int dir)
{
void rotate_servo(int servo,int new_pos,int cur_pos,int dir)
{
  int pos = 0;
  
  if (servo==0)
  {
   
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        base.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        base.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==1)
  {
    
    
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        shoulder.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        shoulder.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==2)
  {
   
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        elbow.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        elbow.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==3)
  {
    
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        wrist1.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        wrist1.write(pos);
        delay(10);
      }      
    }
  }

   if (servo==4)
  {
   
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        wrist2.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        wrist2.write(pos);
        delay(10);
      }      
    }
  }
  
}
}

int new_pos[5];
void servo_cb( const rospy_tutorials::Floats& cmd_msg){
  nh.loginfo("Command Received");
  
 new_pos[0]=cmd_msg.data[0];
 new_pos[1]= cmd_msg.data[1];
 new_pos[2]= cmd_msg.data[2];
 new_pos[3]= cmd_msg.data[3];
 new_pos[4]=cmd_msg.data[4];
 a0 = new_pos[0];
 a4 = new_pos[4];
  
  int i=0;

  for(i=0;i<5;i++)
  {
    if (new_pos[i]>cur_pos[i])
    {
      rotate_servo(i,new_pos[i],cur_pos[i],1);
      cur_pos[i]=new_pos[i];
        
    }
    else if(new_pos[i]<cur_pos[i])
    {
      rotate_servo(i,new_pos[i],cur_pos[i],-1);
      cur_pos[i]=new_pos[i];
    }
    
  }
  
}

void callback(const robotic_arm_pkg::Floats_array::Request & req, robotic_arm_pkg::Floats_array::Response & res)
{
  // Simulate function running for a non-deterministic amount of time
  

  res.res_length=5;
  readbase = analogRead(A0);
  readshoulder=analogRead(A1);
  readelbow=analogRead(A2);
  readwrist1=analogRead(A3);
  readwrist2=analogRead(A4);
  
  res.res[0]=a0;
  //map(readbase,114,430,0,180);
  res.res[1]=map(readshoulder,117,432,0,180);
  res.res[2]=map(readelbow,114,430,0,180);
  res.res[3]=map(readwrist1,116,444,0,180);
  res.res[4]=a4;
  //map(readwrist2,114,430,0,180);

  return;
  
}



ros::Subscriber<rospy_tutorials::Floats> sub("/joints_to_aurdino", servo_cb);
ros::ServiceServer<robotic_arm_pkg::Floats_array::Request, robotic_arm_pkg::Floats_array::Response> server("/read_joint_state",&callback);


void setup(){
nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertiseService(server);

  claw.attach(6);
  wrist2.attach(7);
  base.attach(8);
  shoulder.attach(9);
  elbow.attach(10);
  wrist1.attach(11);
  
  base.write(90);
  shoulder.write(90);
  elbow.write(90);
  wrist1.write(90);
  wrist2.write(0);
  //claw.write(0);

  
  
}

void loop(){

  nh.spinOnce();
}
