% 20200102 Minimum Snap programmed by jacky.kong

clc;clear all;

% waypoints without attitude constraints
% first element is the sequence number of the waypoint
% can be empty 3 4 0 0 3 3.0 -0.5 0.5 4 4 10 0
 waypts_noatti = [2 1 0 0
                    3 1 2 0
%                     4 3 0 0
%                     5 4 0.5 0
                    ]';
%             
% waypoints with attitude constraints(first element is the sequence number of the waypoint)
waypts_atti = [1 0.0 0.0 0.0 1.0 0.0 0.0 0.0;
               %2 2.0 -1 1.0 0.7090   0.7053     0         0;
               %2 2.0 -1.0 1.0 0.8660       0.5000      0         0;
               %2 2.0 -1.0 1.0 0.9239    0.3827         0         0;
               %2 2 -1 0 0.9990    0.0436         0         0;
               6 0.0 2.0 0.0 1.0 0.0 0.0 0.0]';

% waypts_atti = [1 0.0 0.0 0.0 1.0 0.0 0.0 0.0;
%                2 4.0 0.0 0.0 1.0 0.0 0.0 0.0]';

% waypts_noatti = [2 0.1 -0.5 0.5;
%                  3 0.1 -0.7 0.3;
%                  4 -0.1 -0.9 0.1; ]';
%              
% waypts_atti = [1 0.1 -0.3 0.7 1.0 0.0 0.0 0.0;
%                5 -0.1 -1.1 0.1 1.0 0.0 0.0 0.0]';
            
% start state and final state 
v0 = [0 0 0]';
v_end = [0 0 0]';

% declaration
flag_corridor = 0;
corridor_r = 3;
N_order = 5;
optimize_order = 3;% 4snap , 3jerk
continous_order =2;

tic
% generate corridor 
[cons_waypts new_waypts] = generate_corridor(waypts_noatti,waypts_atti,corridor_r);

% constant velocity time allocation
velocity = 1;
ts  = arrangeTbydist(new_waypts, velocity);
ts_smallsize = arrangeTbydist(cons_waypts,velocity);

% generate trajectory
[polys_x polys_y polys_z] = SE3byaccel(new_waypts,waypts_atti,cons_waypts,N_order,ts,ts_smallsize,v0,v_end,corridor_r,flag_corridor,optimize_order,continous_order);
% [polys_x polys_y polys_z] = closeform(new_waypts,waypts_atti,cons_waypts,N_order,ts,ts_smallsize,v0,v_end,corridor_r,flag_corridor,optimize_order,continous_order);

toc

tt = 0:0.01:ts(end);
% ts_smallsize = ts;
xx = polys_vals(polys_x,ts,tt,0);
yy = polys_vals(polys_y,ts,tt,0);
zz = polys_vals(polys_z,ts,tt,0);
vx = polys_vals(polys_x,ts,tt,1);
vy = polys_vals(polys_y,ts,tt,1);
vz = polys_vals(polys_z,ts,tt,1);
ax = polys_vals(polys_x,ts,tt,2);
ay = polys_vals(polys_y,ts,tt,2);
az = polys_vals(polys_z,ts,tt,2);
%3d plot
% figure;
% plot3(xx,yy,zz,'r*');
% hold on;
% quiver3(xx,yy,zz,ax,ay,az+9.8,3);
% quiver3(xx,yy,zz,vx,vy,vz,2);

%2d plot
figure;
plot(cons_waypts(1,:),cons_waypts(2,:),'b*');
hold on;
plot(xx,yy,'r');

pitch_angle = atan2(ax,az+9.8)./pi.*180;
roll_angle = atan2(ay,az+9.8)./pi.*180;
% figure;
% hold on;
% plot(tt,pitch_angle);
% plot(tt,roll_angle);

flight_data = [tt' xx' yy' zz' vx' vy' vz' ax' ay' az'];
fid=fopen('flight_data.txt','wt');%写入文件路径
[m,n]=size(flight_data);
 for i=1:1:m
    for j=1:1:n
       if j==n
         fprintf(fid,'%f\n',flight_data(i,j));
      else
        fprintf(fid,'%f\t',flight_data(i,j));
       end
    end
end
fclose(fid);