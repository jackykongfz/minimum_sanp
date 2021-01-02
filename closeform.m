function [polys_x polys_y polys_z] = closeform(new_waypts,waypts_atti,cons_waypts,N_order,ts,ts_smallsize,v0,v_end,corridor_r,flag_corridor,optimize_order,continous_order)

% number of ploynomial 
n_poly = length(new_waypts(1,:))-1;
n_coef = N_order+1;
n_waypts = length(cons_waypts(1,:));

% compute Q
% xyz
Q_all = zeros(n_poly*(n_coef)*3);
for j = 0:2
    for i = 1:n_poly
        Q_all(j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef,j*n_poly*n_coef+(i-1)*n_coef+1:j*n_poly*n_coef+(i)*n_coef) = computeQ(N_order,optimize_order,ts(i),ts(i+1));

    end
end
b_all = zeros(size(Q_all,1),1);

% compute Tk   Tk(i,j) = ts(i)^(j-1)
tk = zeros(n_poly+1,n_coef);
for i = 1:n_coef
    tk(:,i) = ts(:).^(i-1);
end

% compute A (n_continuous*2*n_poly) * (n_coef*n_poly)
% represent 
n_continuous = continous_order+1;  % 1:p  2:pv  3:pva  4:pvaj  5:pvajs
A = zeros(n_continuous*2*n_poly*3,n_coef*n_poly*3);
A_temp = zeros(n_continuous*2*n_poly,n_coef*n_poly);
for i = 1:n_poly
    for j = 1:n_continuous
        for k = j:n_coef
            if k==j
                t1 = 1;
                t2 = 1;
            else %k>j
                t1 = tk(i,k-j+1);
                t2 = tk(i+1,k-j+1);
            end
            A_temp(n_continuous*2*(i-1)+j,n_coef*(i-1)+k) = prod(k-j+1:k-1)*t1;
            A_temp(n_continuous*2*(i-1)+n_continuous+j,n_coef*(i-1)+k) = prod(k-j+1:k-1)*t2;
        end
    end
end
for i = 1:3
    A((i-1)*n_continuous*2*n_poly+1:i*n_continuous*2*n_poly,(i-1)*n_coef*n_poly+1:i*n_coef*n_poly) = A_temp;
end

% compute M
M = zeros(n_poly*2*n_continuous*3,n_continuous*(n_poly+1)*3);
M_temp = zeros(n_poly*2*n_continuous,n_continuous*(n_poly+1));
for i = 1:n_poly*2
    j = floor(i/2)+1;
    rbeg = n_continuous*(i-1)+1;
    cbeg = n_continuous*(j-1)+1;
    M_temp(rbeg:rbeg+n_continuous-1,cbeg:cbeg+n_continuous-1) = eye(n_continuous);
end
for i = 1:3
    M((i-1)*n_continuous*2*n_poly+1:i*n_continuous*2*n_poly,(i-1)*n_continuous*(n_poly+1)+1:i*n_continuous*(n_poly+1)) = M_temp;
end

%compute C
num_d = (continous_order+1)*(n_poly+1)*3;
C = eye(num_d);
fix_idx = zeros(1,3*length(cons_waypts(1,:))+continous_order*3*2);
d_F = zeros(3*length(cons_waypts(1,:))+continous_order*3*2,1);
fix_idxanddf = zeros(3*length(cons_waypts(1,:))+continous_order*3*2,2);

value = 0;
pos2 = 1;
% middle waypoints position constraints
for i = 1:length(cons_waypts(1,:))
    %find waypoints ts position
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

    %x direction
    fix_idx((i-1)*3+1) = (pos2-1)*(continous_order+1)+1;
    d_F((i-1)*3+1) = cons_waypts(1,i);
    %y direction
    fix_idx((i-1)*3+2) = (continous_order+1)*(n_poly+1)+(pos2-1)*(continous_order+1)+1;
    d_F((i-1)*3+2) = cons_waypts(2,i);
    %z direction
    fix_idx((i-1)*3+3) = (continous_order+1)*(n_poly+1)*2+(pos2-1)*(continous_order+1)+1;
    d_F((i-1)*3+3) = cons_waypts(3,i);
end

neq = (length(cons_waypts(1,:))-1)*3+3;
neq = neq+1;
% start point
for i = 1:continous_order
    %x direction
    fix_idx(neq) = 1+i;
    d_F(neq) = 0;
    neq = neq+1;
    %y direction
    fix_idx(neq) = (continous_order+1)*(n_poly+1)+1+i;
    d_F(neq) = 0;
    neq = neq+1;
    %z direction
    fix_idx(neq) = (continous_order+1)*(n_poly+1)*2+1+i;
    d_F(neq) = 0;
    neq = neq+1;
end
% end point
for i = 1:continous_order
    %x direction
    fix_idx(neq) = (continous_order+1)*(n_poly+1)-continous_order+i;
    d_F(neq) = 0;
    neq = neq+1;
    %y direction
    fix_idx(neq) = (continous_order+1)*(n_poly+1)*2-continous_order+i;
    d_F(neq) = 0;
    neq = neq+1;
    %z direction
    fix_idx(neq) = (continous_order+1)*(n_poly+1)*3-continous_order+i;
    d_F(neq) = 0;
    neq = neq+1;
end

%fix_idx = [1:(continous_order+1):num_d,2:(continous_order+1),num_d-(continous_order+1)+1:num_d];
fix_idx = fix_idx';
fix_idxanddf(:,1) = fix_idx;
fix_idxanddf(:,2) = d_F;
fix_idxanddf = sortrows(fix_idxanddf,1);
d_F = fix_idxanddf(:,2);
free_idx = setdiff(1:num_d,fix_idxanddf(:,1));
C = [C(:,fix_idxanddf(:,1)) C(:,free_idx)];

% %compute K
% K = pinv(M)*C;
% R = (K')*Q_all*K;
AiMC = inv(A)*M*C;
R = AiMC'*Q_all*AiMC;

n_fix = length(fix_idx);
Rff = R(1:n_fix,1:n_fix);
Rpp = R(n_fix+1:end,n_fix+1:end);
Rfp = R(1:n_fix,n_fix+1:end);
Rpf = R(n_fix+1:end,1:n_fix);

d_P = -inv(Rpp)*Rfp'*d_F;

% p = K*[d_F;d_P];
p = AiMC*[d_F;d_P];

polys_x = reshape(p(1:length(p)/3),n_coef,n_poly);
polys_y = reshape(p(length(p)/3+1:2*length(p)/3),n_coef,n_poly);
polys_z = reshape(p(2*length(p)/3+1:length(p)),n_coef,n_poly);

end