%[ip, fs] = audioread('audioHighE.mp4', [1 50000]); %[1 20000]
a = csvread('low_e_20k.csv', 10);
ip = a(:,2);
ip = ip*100;
ip = ip -1.5 %-2.5;
fs = 20e3;
%Down = decimate(ip,2);
%B = 12;
%delta = 2/2^B;
%ip = round(ip/delta)*delta
%disp(ip)

%Down = downsample(ip,2);
%ip = Down;
min_expected_period = 50;
max_expected_period = 1000;
frame_len = 1000;



for k = 1 : length(ip)/(frame_len -1)
   range = (k-1)*frame_len + 1:k*frame_len;
   frame = ip(range);
     %frame = ip ;
    
    fftx = fft(frame);
    magSquare = abs(fftx).*abs(fftx);
    rxx = ifft(magSquare);
    
    x = 1:1:length(rxx);
    plot(x, rxx)
    pause
    
end
