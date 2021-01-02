%read simulator data
fid=fopen('simu_data.txt','r');%写入文件路径
n = 8;
m = 1497;
simu_data = zeros(m,n);
 for i=1:1:m
    for j=1:1:n
       if j==n
         simu_data(i,j)=fscanf(fid,'%f\n',[1 1]);
       else
         simu_data(i,j)=fscanf(fid,'%f',[1 1]);
       end
    end
end
fclose(fid);

q = simu_data(:,5:8);
dq = (q(2:end,:) - q(1:(end-1),:))./0.01;
w = [-2*q(2) 2*q(1) -2*q(4) 2*q(3);
    -2*q(3) 2*q(4) 2*q(1) -2*q(2);
     -2*q(4) -2*q(3) 2*q(2) 2*q(1);]*(dq');
% figure;
% hold on;
% % plot(simu_data(2:end,1),w(1,:),'b');
% % plot(simu_data(2:end,1),w(2,:),'r');
% % plot(simu_data(2:end,1),w(3,:),'y');
% 
% plot(simu_data(3:end,1),(w(1,2:end)-w(1,1:end-1))./0.01,'b');
% plot(simu_data(3:end,1),(w(2,2:end)-w(2,1:end-1))./0.01,'r');
% % plot(simu_data(3:end,1),(w(3,2:end)-w(3,1:end-1))./0.01,'y');

angle_x = zeros(m,1);
angle_y = zeros(m,1);
angle_z = zeros(m,1);
a_simu = zeros(3,m);
for i = 1:m
    [angle_x(i) angle_y(i) angle_z(i)] = quat2angle(q(i,:),'XYZ');
    
    a_simu(1:3,i)  = quat2dcm(q(i,:))*[0; 0; 1];
end
% figure;
% hold on;
% plot(simu_data(1:end,1),angle_x./pi*180,'b');
% plot(simu_data(1:end,1),angle_y./pi*180,'r');
% plot(simu_data(1:end,1),angle_z./pi*180,'y');
% 
figure;
hold on;
plot(simu_data(1:end,1),atan2(a_simu(1,:),a_simu(3,:))./pi.*180,'b');%roll
plot(simu_data(1:end,1),atan2(a_simu(2,:),a_simu(3,:))./pi.*180,'r');%pitch
% 
% figure;
% hold on;
% plot(simu_data(1:end,1),a_simu(1,:),'b');
% plot(simu_data(1:end,1),a_simu(2,:),'r');
% plot(simu_data(1:end,1),a_simu(3,:),'g');
    
figure;
plot3(xx,yy,zz,'r*');
hold on;
plot3(simu_data(:,3),simu_data(:,2),simu_data(:,4)-5,'b*');
quiver3(simu_data(:,3),simu_data(:,2),simu_data(:,4)-5,xx'-simu_data(:,3),yy'-simu_data(:,2),zz'-(simu_data(:,4)-5),4);

% figure;
% plot(tt,xx,'r*');
% hold on;
% plot(simu_data(:,1),simu_data(:,2),'b*');

% figure;
% plot(simu_data(:,1),simu_data(:,5));