%[ip, fs] = audioread('440pure.mp4', [1 20000]); %[1 20000]
%a = csvread('low_e_10k.csv', 11);
a = csvread('high_e_10kHz.csv', 11);
% a = csvread('d_10k.csv', 11);
%a = csvread('a_10k.csv', 11);
%a = textread('a_10k.csv',%d, 11);
ip = a(:,2);
axis = a(:,1);


%Sampling rate
fs = 10e3;


min_expected_period = 50;
max_expected_period = 500;
%number of samples
frame_len = 1024;


 
figure(1)
plot(axis, ip);
xlabel('Time')
xlim([0 .020])
ylabel('Voltage')

%scale CSV
ip = ip*100;

%center at zero
avg = mean(ip);
ip = ip -avg;



for k = 1 : length(ip)/(frame_len -1)
   range = (k-1)*frame_len + 1:k*frame_len;
   frame = ip(range);
     %frame = ip ;
    
     
    %Perform autocorrelation
    %this is the equivalent computation as a series of discrete sums
    %but in the frequency domain
    fftx = fft(frame);
    magSquare = abs(fftx).*abs(fftx);
    rxx = ifft(magSquare);
    
    
    %normalized by the amount of energy in the signal
    %the origin of the autocorrelated is the energy, E, contained
    %in the signal
    ryy = rxx/rxx(1);
    
   
    %zero out negative correlations
    index = find(ryy<0);
    ryy(index) = 0;
    
    %find standard deviation and mean
    dev = std(ryy);
    avg = mean(ryy);
    
    
    %zero out terms less than threshold
    indexes = find(ryy<(avg+dev));
    
    ryy(indexes) = 0;
    
    %onlyPeaks = ryy(indexes);
    onlyPeaks = ryy;
    
    
    %%perform rudimentary peak detection
    for i = 2:(length(onlyPeaks)-1)
        
        
        if((onlyPeaks(i) - onlyPeaks(i-1) > 0) && ((onlyPeaks(i+1) - onlyPeaks(i)) < 0))
            thePeakIs = i; 
             
        elseif((onlyPeaks(i) - onlyPeaks(i-1) > 0))
            continue
             
        elseif((onlyPeaks(i+1) - onlyPeaks(i)) < 0)
            continue
        end
    end
    
    %returns mirror image on other end of array
    %calculate note value
    note = fs/(frame_len-thePeakIs)
    
            
  
      
    %create x-axis dimension
    x = 1:1:length(rxx);
    
    figure(2)
    plot(x, ryy)
    xlabel('n (sample)')
    ylabel('Magnitude (Normalized)')
    
    %pause and wait for use input
    pause
    
end
