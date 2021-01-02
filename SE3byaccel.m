function [polys_x polys_y polys_z] = SE3byaccel(new_waypts,waypts_atti,cons_waypts,N_order,ts,ts_smallsize,v0,v_end,corridor_r,flag_corridor,optimize_order,continous_order)

% number of ploynomial 
% n_poly = length(cons_waypts(1,:))-1;
n_poly = length(new_waypts(1,:))-1;
n_coef = N_order+1;
n_waypts = length(cons_waypts(1,:));

% % nondimensionalization
% ts = ts./(ts(end));
% ts_smallsize = ts_smallsize./ts_smallsize(end);

% compute Q
% xyz
 Q_all = zeros(n_poly*(n_coef)*3);
% Q_all = [];
% for j = 1:3
% for i=1:n_poly
%     Q_all = blkdiag(Q_all,computeQ(N_order,optimize_order,ts(i),ts(i+1)));
% end
% end

% n_coef = n_coef-1;
for j = 0:2
    for i = 1:n_poly
        Q_all(j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef,j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef) = computeQ(N_order,optimize_order,ts(i),ts(i+1));
        %disp(size(Q_all(j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef,j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef)));
        %disp(size(computeQ(N_order,optimize_order,ts(i),ts(i+1))));
    end
end
% n_coef = n_coef+1;
b_all = zeros(size(Q_all,1),1);

% Equation constraint
Aeq = zeros(3*(n_poly-1)*(continous_order+1) + 2*length(waypts_atti(1,:)) + 3*length(cons_waypts(1,:)) + 2*3,size(Q_all,1));
%            continous constraints          acceleration constraints       pv constraints 
beq = zeros(length(Aeq(:,1)),1);

neq = 1;
%continous constraints
   for j = 1:n_poly-1
       for k = 1:continous_order+1
           tvec = calc_tvec(ts(j+1),N_order,k-1);
           Aeq(neq,n_coef*(j-1)+1:n_coef*(j+1)) = [tvec -tvec];         % x direction
           neq = neq + 1;
           Aeq(neq,n_poly*n_coef+n_coef*(j-1)+1:n_poly*n_coef+n_coef*(j+1)) = [tvec -tvec];         % y direction
           neq = neq + 1;
           Aeq(neq,2*n_poly*n_coef+n_coef*(j-1)+1:2*n_poly*n_coef+n_coef*(j+1)) = [tvec -tvec];         % z direction
           neq = neq + 1;
       end
   end
   
% start/end pv constraints
Aeq(neq:neq+1, 1:n_coef) = [calc_tvec(ts(1),N_order,0);calc_tvec(ts(1),N_order,1);];
neq = neq +2;
Aeq(neq:neq+1, n_coef*(n_poly-1)+1:n_coef*n_poly) = [calc_tvec(ts(end),N_order,0);calc_tvec(ts(end),N_order,1);];
neq = neq +2;
Aeq(neq:neq+1, n_coef*n_poly+1:n_coef*n_poly+n_coef) = [calc_tvec(ts(1),N_order,0);calc_tvec(ts(1),N_order,1);];
neq = neq +2;
Aeq(neq:neq+1, n_coef*n_poly+n_coef*(n_poly-1)+1:n_coef*n_poly+n_coef*n_poly) = [calc_tvec(ts(end),N_order,0);calc_tvec(ts(end),N_order,1);];
neq = neq +2;
Aeq(neq:neq+1, 2*n_coef*n_poly+1:2*n_coef*n_poly+n_coef) = [calc_tvec(ts(1),N_order,0);calc_tvec(ts(1),N_order,1);];
neq = neq +2;
Aeq(neq:neq+1, 2*n_coef*n_poly+n_coef*(n_poly-1)+1:2*n_coef*n_poly+n_coef*n_poly) = [calc_tvec(ts(end),N_order,0);calc_tvec(ts(end),N_order,1);];
 neq = neq +2;
% beq(neq-12:neq-1) = [cons_waypts(1,1);v0(1);cons_waypts(2,1);v0(2);cons_waypts(3,1);v0(3);
%                     cons_waypts(1,end);v_end(1);cons_waypts(2,end);v_end(2);cons_waypts(3,end);v_end(3);];
beq(neq-12:neq-1) = [cons_waypts(1,1);v0(1);cons_waypts(1,end);v_end(1);cons_waypts(2,1);v0(2);
                    cons_waypts(2,end);v_end(2);cons_waypts(3,1);v0(3);cons_waypts(3,end);v_end(3);];
% % πÈ“ªªØ∫Û
% beq(neq-12:neq-1) = [cons_waypts(1,1);v0(1)*ts(end);cons_waypts(2,1);v0(2)*ts(end);cons_waypts(3,1);v0(3)*ts(end);
%                     cons_waypts(1,end);v_end(1)*ts(end);cons_waypts(2,end);v_end(2)*ts(end);cons_waypts(3,end);v_end(3)*ts(end);];

value = 0;
pos2 = 1;
% middle waypoints position constraints
for i = 2:length(cons_waypts(1,:))-1
    pos = find(ismember(cons_waypts',cons_waypts(:,i)','rows')==1);
    %[value, pos2] = min(abs(ts-ts_smallsize(:,pos)));
    temp = ts_smallsize(:,pos);
    ts_new = zeros(length(ts),1);
    for j = 1:(length(ts))
        if((ts(j)-temp)<0)
            ts_new(j) = -(ts(j)-temp);
        else
            ts_new(j) = (ts(j)-temp);
        end
    end
    %ts_new  = abs(ts-temp);
    value = min(ts_new);
    %pos2 = find(ts_new == value);
    for j=1:length(ts_new)
        if(ts_new(j)==value)
            pos2 = j;
        end
    end

    Aeq(neq, n_coef*(pos2-1)+1:pos2*n_coef) = [calc_tvec(ts(pos2),N_order,0)];
    beq(neq) = cons_waypts(1,i);
    neq = neq+1;
    Aeq(neq, n_coef*n_poly+n_coef*(pos2-1)+1:n_coef*n_poly+pos2*n_coef) = [calc_tvec(ts(pos2),N_order,0)];
    beq(neq) = cons_waypts(2,i);
    neq = neq+1;
    Aeq(neq, 2*n_coef*n_poly+n_coef*(pos2-1)+1:2*n_coef*n_poly+pos2*n_coef) = [calc_tvec(ts(pos2),N_order,0)];
    beq(neq) = cons_waypts(3,i);
    neq = neq+1;
end

coder.extrinsic('quat2dcm');
coder.extrinsic('quadprog');
a_dir = [0;0;1];

% acceleration constraints
for i = 1:length(waypts_atti(1,:))
    q = waypts_atti(5:8,i);
    Dcm = quat2dcm(q');
    a_dir = Dcm*[0; 0; 1];
%     a_dir = a_dir - [0;0;9.8];
%     xtheta = (a_dir(1)/a_dir(3));% tan pitch ANGLE
%     ytheta = (a_dir(2)/a_dir(3));% tan roll ANGLE
%     
%     if xtheta > 115 || (isnan(xtheta) && q(2)>0)
%         xtheta = tan(89.5/180*pi);
%     end
%     if ytheta > 115 || (isnan(ytheta) && q(3)>0)
%         ytheta = tan(89.5/180*pi);
%     end
%     if xtheta < -115 || (isnan(xtheta) && q(2)<0)
%         xtheta = tan(-89.5/180*pi);
%     end
%     if ytheta < -115 || (isnan(ytheta) && q(3)<0)
%         ytheta = tan(-89.5/180*pi);
%     end
    
    pos = find(ismember(cons_waypts',waypts_atti(2:4,i)','rows')==1);
    %[value pos2] = min(abs(ts-ts_smallsize(:,pos)));
    temp = ts_smallsize(:,pos);
    ts_new = zeros(length(ts),1);
    for j = 1:(length(ts))
        if((ts(j)-temp)<0)
            ts_new(j) = -(ts(j)-temp);
        else
            ts_new(j) = (ts(j)-temp);
        end
    end
    %ts_new  = abs(ts-temp);
    value = min(ts_new);
    %pos2 = find(ts_new == value);
    for j=1:length(ts_new)
        if(ts_new(j)==value)
            pos2 = j;
        end
    end
    
     tvec_a = calc_tvec(ts(pos2),N_order,2);

    if pos == length(ts_smallsize)
        pos = pos2;
            % pitch
            Aeq(neq,n_coef*(pos-2)+1:n_coef*(pos-1)) = tvec_a*a_dir(3);
%             Aeq(neq,2*n_coef*n_poly+ n_coef*(pos-2)+1:2*n_coef*n_poly+ n_coef*(pos-1)) = -tvec_a * xtheta;
            Aeq(neq,2*n_coef*n_poly+ n_coef*(pos-2)+1:2*n_coef*n_poly+ n_coef*(pos-1)) = -tvec_a * a_dir(1);
            beq(neq) = 9.8.*a_dir(1);
    
            neq = neq +1;
            % roll
            Aeq(neq,n_coef*n_poly+ n_coef*(pos-2)+1:n_coef*n_poly+n_coef*(pos-1)) = tvec_a*a_dir(3);
            Aeq(neq,2*n_coef*n_poly+ n_coef*(pos-2)+1:2*n_coef*n_poly+ n_coef*(pos-1)) = -tvec_a * a_dir(2);
            beq(neq) = 9.8.*a_dir(2);
    
            neq = neq +1;
    else
        pos = pos2;
    % roll
    Aeq(neq,n_coef*(pos-1)+1:n_coef*pos) = tvec_a* a_dir(3);
    Aeq(neq,2*n_coef*n_poly+ n_coef*(pos-1)+1:2*n_coef*n_poly+ n_coef*pos) = -tvec_a * a_dir(1);
    beq(neq) = 9.8.*a_dir(1);
    
    neq = neq +1;
    % pitch
    Aeq(neq,n_coef*n_poly+ n_coef*(pos-1)+1:n_coef*n_poly+n_coef*pos) = tvec_a* a_dir(3);
    Aeq(neq,2*n_coef*n_poly+ n_coef*(pos-1)+1:2*n_coef*n_poly+ n_coef*pos) = -tvec_a * a_dir(2);
    beq(neq) = 9.8.*a_dir(2);
    
    neq = neq +1;
    end
end

 Aieq = zeros(3*2*(n_poly-1)+(n_poly+1),3*n_coef*n_poly);
 bieq = zeros(3*2*(n_poly-1)+(n_poly+1),1);

if flag_corridor ==1
% corridor constraints

 for i = 1:n_poly-1
     tvec_p = calc_tvec(ts(i+1),N_order,0);
     
     Aieq(6*i-5:6*i-4,n_coef*i+1:n_coef*(i+1)) = [tvec_p;-tvec_p];
     bieq(6*i-5:6*i-4) = [new_waypts(1,i+1)+corridor_r corridor_r-new_waypts(1,i+1)];
     
     Aieq(6*i-3:6*i-2,n_coef*n_poly+n_coef*i+1:n_coef*n_poly+n_coef*(i+1)) = [tvec_p;-tvec_p];
     bieq(6*i-3:6*i-2) = [new_waypts(2,i+1)+corridor_r corridor_r-new_waypts(2,i+1)];
     
     Aieq(6*i-1:6*i,2*n_coef*n_poly+n_coef*i+1:2*n_coef*n_poly+n_coef*(i+1)) = [tvec_p;-tvec_p];
     bieq(6*i-1:6*i) = [new_waypts(3,i+1)+corridor_r corridor_r-new_waypts(3,i+1)];
 end
else
Aieq = [];
bieq = [];
end

%  for i = 1:n_poly+1
%      tvec_a = calc_tvec(ts(i),N_order,2);
%      
%      Aieq(6*(n_poly-1)+i,)
%  end
p = zeros(n_poly*n_coef*3,1);
[p, fval, flag] = quadprog(Q_all,b_all,Aieq,bieq,Aeq,beq);
polys_x = reshape(p(1:length(p)/3),n_coef,n_poly);
polys_y = reshape(p(length(p)/3+1:2*length(p)/3),n_coef,n_poly);
polys_z = reshape(p(2*length(p)/3+1:length(p)),n_coef,n_poly);
disp(fval);

end