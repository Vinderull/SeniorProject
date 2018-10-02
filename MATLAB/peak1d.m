function peak = peak1d(A, i, j)

        m = floor((i+j)/2);
        
        if((A(m-1) <= A(m)) && (A(m+1) >= A(m)))
            peak = m;
            
        elseif(A(m-1) > A(m))
            peak = peak1d(A,i, m-1);
            
        elseif(A(m) < A(m+1)) 
            peak  = peak1d(A,m+1, j);
            
        end
end
