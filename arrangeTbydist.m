function ts = arrangeTbydist(waypts,velocity)
%     x = waypts(:,2:end) - waypts(:,1:end-1);
%     dist = sum(x.^2,1).^0.5;
%     T = sum(dist)/velocity;
%     k = T/sum(dist);
%     ts = [0 cumsum(dist*k)];

%new time allocation
    x = waypts(:,2:end) - waypts(:,1:end-1);
    dist = sum(x.^2,1).^0.5;
    T = sum(dist)/velocity;
    
    k = T/sum(dist);
    
    coder.extrinsic('norm');
    T_seg = dist*k;
    for i = 2:length(T_seg)-1
        theta = acos((dot(x(:,i+1),x(:,i-1)))/(sum(x(:,i+1).^2).^0.5 * sum(x(:,i-1).^2).^0.5)) ./pi.*180;
        disp(theta);
        T_seg(i) = T_seg(i) * (1 - 0.6*theta/180);
    end
    
%     ts = [0 cumsum(dist*k)];
    ts = [0 cumsum(T_seg)];

end