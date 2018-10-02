[ip, fs] = audioread('audioHighE.mp4', [1 20000]); %[1 20000]
%a = csvread('low_e_10k.csv', 11);
%a = csvread('high_e_10kHz2.csv', 11);
% a = csvread('d_10k.csv', 11);
% ip = a(:,2);
% axis = a(:,1);
% ip = ip*100;
% avg = mean(ip)
%  ip = ip -avg %-2.5;
% fs = 10e3;


min_expected_period = 50;
max_expected_period = 500;
frame_len = 1000;

% figure(1)
% plot(axis, ip);



for k = 1 : length(ip)/(frame_len -1)
   range = (k-1)*frame_len + 1:k*frame_len;
   frame = ip(range);
     %frame = ip ;
    
    fftx = fft(frame);
    magSquare = abs(fftx).*abs(fftx);
    rxx = ifft(magSquare);
    
    ryy = rxx/rxx(1);
    
   
    index = find(ryy<0);
    ryy(index) = 0;
    
    dev = std(ryy);
    avg = mean(ryy);
    
    indexes = find(ryy<(avg+dev));
    
    ryy(indexes) = 0;
    
    %onlyPeaks = ryy(indexes);
    onlyPeaks = ryy;
    
    for i = 2:(length(onlyPeaks)-1)
        
        if((onlyPeaks(i) - onlyPeaks(i-1) > 0) && ((onlyPeaks(i+1) - onlyPeaks(i)) < 0))
            thePeakIs = i
             
        elseif((onlyPeaks(i) - onlyPeaks(i-1) > 0))
            continue
             
        elseif((onlyPeaks(i+1) - onlyPeaks(i)) < 0)
            continue
        end
    end
    
    note = fs/(frame_len-thePeakIs)
    
            
  
    %samp = peak1d(ryy,1, 500)
    
    [maxy loc] = max(ryy);
    
%     for i = 1 :length(ryy)
%          
%         if
%     
    
  
      

    x = 1:1:length(rxx);
    
    figure(2)
    plot(x, ryy)
    pause
    
end
