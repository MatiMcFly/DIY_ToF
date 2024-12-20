% calculate the median frequency component
% by splitting the area under the spectrum envelope ROI in two equal parts
medianIdx = 0;
for i=1:length(spectrum_env_roi)
    if sum(spectrum_env_roi(1:i)) > meanVal * length(spectrum_env_roi) / 2
        medianIdx = i;
        break;
    end
end

f_median = (medianIdx+leftIdx - N/2) * fs/N;