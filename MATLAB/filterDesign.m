%%filters


n = 8;
f = 500;

[zb,pb,kb] = butter(n,2*pi*f,'s');
[bb,ab] = zp2tf(zb,pb,19*kb);
[hb,wb] = freqs(bb,ab,4096);
freqs(bb,ab,4096);

plot(wb/(2*pi),mag2db(abs(hb)))
xlim([0 2000])

% s = j*2*pi*f;
% wo = 2*pi*f;
% 
% %denom = 1 + (1/(wo*Q))*s + 1/(w0^2)*s^2;
% 
% firststage = s^2 + 0.5165*s + 1;
% secondstage = s^2 + 1.4142*s + 1;
% thirdstage = s^2 + 1.9319*s + 1;

%C1C2R1R2 = 1
%C2(R1+R2) = s term coefficient




%      H*w0^2
%------------------
%s^2 + a*wo*s + wo^2


%Vo =     H * (R1R2C1C2)^1/2
%----------------------------------------------------------------
%Vin   s^2 + s[((1/R1+1/R2))*(C1^1/2) + (1-H)/R2C2] + 1/R1R2C1C2

%Choose c1 = 100nF  and R3
%k = 2*pi*Fo*C1
%m = (a^2)/4 + (H-1)
%C2 = mC1
%R1 = 2/(a*k)
%R2 = a/(2*m*k)
%R4 = R3/(H-1);

% wo = 2*pi*f
% a0*wo = .3902
% a1*w0 = 1.1111;
% a2*w0 = 1.6629
% a3*w0 = 1.9619


firststage = s^2 + 0.3902*s + 1;
secondstage = s^2 + 1.1111*s + 1;
thirdstage = s^2 + 1.6629*s + 1;
fourthstage = s^2 + 1.9619*s + 1;
% 
% final = tf(12, firststage*secondstage*thirdstage)
% bode(final, opts)