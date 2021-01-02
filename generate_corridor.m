function [cons_waypts new_waypts2] = generate_corridor(waypts_noatti,waypts_atti,r)

% regenerate waypoints
if isempty(waypts_noatti)
    new_waypts = zeros(3, length(waypts_atti(1,:)));
else
    new_waypts = zeros(3, length(waypts_atti(1,:))+ length(waypts_noatti(1,:)));
end

temp_waypts = zeros(4,length(new_waypts(1,:)));
temp_waypts(:,1:length(waypts_atti(1,:))) = waypts_atti(1:4,:);
if isempty(waypts_noatti)==0
    temp_waypts(:,length(waypts_atti(1,:))+1:length(waypts_atti(1,:))+length(waypts_noatti(1,:))) = waypts_noatti(1:4,:);
end

% resort 
temp2_waypts = sortrows(temp_waypts',1);
new_waypts = temp2_waypts(:,2:4)';

% linear interpolation
new_waypts2 = new_waypts(:,1);
for i=2:size(new_waypts,2)
    x1 = new_waypts(1,i-1);
    y1 = new_waypts(2,i-1);
    z1 = new_waypts(3,i-1);
    x2 = new_waypts(1,i);
    y2 = new_waypts(2,i);
    z2 = new_waypts(3,i);
    temp = sqrt((x1-x2)^2+(y1-y2)^2+(z1-z2)^2);
    n = ceil(temp/r)+1;
    sample_pts = [linspace(x1,x2,n);linspace(y1,y2,n);linspace(z1,z2,n)];
    new_waypts2 = [new_waypts2 sample_pts(:,2:end)];
end

cons_waypts = new_waypts;

end